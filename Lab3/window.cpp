#include <QGridLayout>

#include "window.h"

Window::Window()
{
    game.reset(new Game());
    translater.reset(new Translater());
    dataMaster.reset(new DataMaster());
    renderArea.reset(new RenderArea(game->GetMatrix()));
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
            game.get(), &Game::ChangeRect);
    connect(game.get(), &Game::Changed,
            renderArea.get(), &RenderArea::Update);
    connect(playButton.get(), &QPushButton::pressed,
            game.get(), &Game::Activate);
    connect(stopButton.get(), &QPushButton::pressed,
            game.get(), &Game::Diactivate);
    connect(clearButton.get(), &QPushButton::pressed,
            game.get(), &Game::Clear);
    connect(setRulesButton.get(), &QPushButton::pressed,
            this, &Window::SetRulesForGame);
    connect(setSizeButton.get(), &QPushButton::pressed,
            this, &Window::ResizeGame);
    connect(translater.get(), &Translater::TranslatedRules,
            game.get(), &Game::SetRules);
    connect(translater.get(), &Translater::TranslatedSize,
            game.get(), &Game::Resize);
    connect(saveButton.get(), &QPushButton::pressed,
            this, &Window::SaveGame);
    connect(loadButton.get(), &QPushButton::pressed,
            this, &Window::LoadGame);
}

void Window::SetRulesForGame(){
    if(game->GetPlay()){
        return;
    }
    translater->TranslateRules(modeLine->text());
}

void Window::ResizeGame(){
    if(game->GetPlay()){
        return;
    }
    translater->TranslateSize(widthLine->text(), heightLine->text());
}

void Window::SaveGame(){
    if(game->GetPlay()){
        return;
    }
    dataMaster->Save(game->GetMatrix(), game->GetRules());
}

void Window::LoadGame(){
    if(game->GetPlay()){
        return;
    }
    dataMaster->Load(game->GetMatrix(), game->GetRules());
}
