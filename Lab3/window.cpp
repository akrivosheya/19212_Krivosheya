#include "window.h"
#include <QGridLayout>

Window::Window()
{
    game = new Game();
    renderArea = new RenderArea(game->GetMatrix());
    playButton = new QPushButton(tr("&Play"));
    stopButton = new QPushButton(tr("&Stop"));
    saveButton = new QPushButton(tr("&Save"));
    loadButton = new QPushButton(tr("&Load"));
    setRulesButton = new QPushButton(tr("&Set rules"));
    setSizeButton = new QPushButton(tr("&Set size"));
    modeLine = new QLineEdit();
    widthLine = new QLineEdit();
    heightLine = new QLineEdit();
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(playButton, 0, 0);
    mainLayout->addWidget(stopButton, 0, 1);
    mainLayout->addWidget(saveButton, 0, 2);
    mainLayout->addWidget(loadButton, 0, 3);
    mainLayout->addWidget(setRulesButton, 0, 4);
    mainLayout->addWidget(setSizeButton, 0, 5);
    mainLayout->addWidget(widthLine, 1, 5);
    mainLayout->addWidget(heightLine, 2, 5);
    mainLayout->addWidget(modeLine, 3, 5);
    mainLayout->addWidget(renderArea, 1, 0, 4, 5);
    setLayout(mainLayout);
    setWindowTitle(tr("The Life"));
    connect(renderArea, &RenderArea::Clicked,
            game, &Game::ChangeRect);
    connect(game, &Game::Changed,
            renderArea, &RenderArea::Update);
    connect(playButton, &QPushButton::pressed,
            game, &Game::Activate);
    connect(stopButton, &QPushButton::pressed,
            game, &Game::Diactivate);
    connect(setRulesButton, &QPushButton::pressed,
            this, &Window::GiveRulesForGame);
}

Window::~Window()
{
    delete game;
    delete renderArea;
    delete playButton;
    delete stopButton;
    delete saveButton;
    delete loadButton;
    delete setRulesButton;
    delete setSizeButton;
    delete modeLine;
    delete widthLine;
    delete heightLine;
}

void Window::GiveRulesForGame(){
    game->SetRules(modeLine->text());
}
