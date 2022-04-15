#include <QGridLayout>

#include "window.h"

Window::Window()
{
    game.reset(new Game());
    translater.reset(new Translater());
    dataMaster.reset(new DataMaster());
    renderArea.reset(new RenderArea(game.get()));
    playButton.reset(new QPushButton(tr("&Play")));
    stopButton.reset(new QPushButton(tr("&Stop")));
    saveButton.reset(new QPushButton(tr("&Save")));
    loadButton.reset(new QPushButton(tr("&Load")));
    clearButton.reset(new QPushButton(tr("&Clear")));
    setRulesButton.reset(new QPushButton(tr("&Set rules")));
    setSizeButton.reset(new QPushButton(tr("&Set size")));
    modeLine.reset(new QLineEdit());
    widthLine.reset(new QLineEdit());
    heightLine.reset(new QLineEdit());
    widthLabel.reset(new QLabel(tr("Width:"), nullptr));
    heightLabel.reset(new QLabel(tr("Height:"), nullptr));
    informant.reset(new Informant());
    timer.reset(new Timer());

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(playButton.get(), 0, 0);
    mainLayout->addWidget(stopButton.get(), 0, 1);
    mainLayout->addWidget(saveButton.get(), 0, 2);
    mainLayout->addWidget(loadButton.get(), 0, 3);
    mainLayout->addWidget(clearButton.get(), 0, 4);
    mainLayout->addWidget(setRulesButton.get(), 0, 5, 1, 2);
    mainLayout->addWidget(setSizeButton.get(), 2, 5, 1, 2);
    mainLayout->addWidget(widthLabel.get(), 3, 5);
    mainLayout->addWidget(heightLabel.get(), 3, 6);
    mainLayout->addWidget(widthLine.get(), 4, 5);
    mainLayout->addWidget(heightLine.get(), 4, 6);
    mainLayout->addWidget(modeLine.get(), 1, 5, 1, 2);
    mainLayout->addWidget(renderArea.get(), 1, 0, 20, 5);
    setLayout(mainLayout);
    setWindowTitle(tr("The Life"));

    connect(renderArea.get(), &RenderArea::Clicked,
            this, &Window::ChangeRectOfMatrix);
    connect(playButton.get(), &QPushButton::pressed,
            this, &Window::ActivateGame);
    connect(stopButton.get(), &QPushButton::pressed,
            this, &Window::DiactivateGame);
    connect(clearButton.get(), &QPushButton::pressed,
            this, &Window::ClearGame);
    connect(setRulesButton.get(), &QPushButton::pressed,
            this, &Window::SetRulesForGame);
    connect(setSizeButton.get(), &QPushButton::pressed,
            this, &Window::ResizeGame);
    connect(saveButton.get(), &QPushButton::pressed,
            this, &Window::SaveGame);
    connect(loadButton.get(), &QPushButton::pressed,
            this, &Window::LoadGame);
    connect(timer.get(), &Timer::TimeIsUp,
            this, &Window::PlayGame);
}

void Window::SetRulesForGame(){
    if(game->GetIsPlaying()){
        return;
    }
    std::vector<std::vector<bool> > newRules;
    if(!translater->TranslateRules(modeLine->text(),
                                   newRules)){
        informant->InformWrongRule();
        return;
    }
    game->SetRules(newRules);
}

void Window::ResizeGame(){
    if(game->GetIsPlaying()){
        return;
    }
    std::vector<std::vector<bool>> newMatrix;
    if(!translater->TranslateSize(widthLine->text(),
                              heightLine->text(),
                              newMatrix)){
        informant->InformWrongSize();
        return;
    }
    game->Resize(newMatrix);
    renderArea->Update();
}

void Window::SaveGame(){
    if(game->GetIsPlaying()){
        return;
    }
    QString error;
    int res = dataMaster->Save(game->GetMatrix(),
                               game->GetRules(),
                               error);
    if(res == dataMaster->GetSuccessCode()){
        informant->InformSuccessfulSaving();
        return;
    }
    if(res == dataMaster->GetEmptyCode()){
        informant->InformEmpty();
        return;
    }
    if(res == dataMaster->GetUnableCode()){
        informant->InformUnable(error);
        return;
    }
    if(res == dataMaster->GetFormatCode()){
        informant->InformWrongFormat();
        return;
    }
}

void Window::LoadGame(){
    if(game->GetIsPlaying()){
        return;
    }
    QString error;
    int res = dataMaster->Load(game->GetMatrix(),
                               game->GetRules(),
                               error);
    if(res == dataMaster->GetSuccessCode()){
        informant->InformSuccessfulLoading();
        return;
    }
    if(res == dataMaster->GetUnableCode()){
        informant->InformUnable(error);
        return;
    }
    if(res == dataMaster->GetFormatCode()){
        informant->InformWrongFormat();
        return;
    }
}

void Window::ActivateGame(){
    if(game->GetIsPlaying()){
        return;
    }
    game->Activate();
    timer->StartTimer();
}

void Window::DiactivateGame(){
    if(!game->GetIsPlaying()){
        return;
    }
    game->Diactivate();
    timer->KillTimer();
}

void Window::PlayGame(){
    if(!game->GetIsPlaying()){
        return;
    }
    game->MakeStep();
    renderArea->Update();
}

void Window::ClearGame(){
    if(game->GetIsPlaying()){
        return;
    }
    game->Clear();
    renderArea->Update();
}

void Window::ChangeRectOfMatrix(int idx1, int idx2){
    if(game->GetIsPlaying()){
        return;
    }
    game->ChangeRect(idx1, idx2);
    renderArea->Update();
}
