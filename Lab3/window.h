#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "RenderArea.h"
#include "Game.h"
#include "Test.h"

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();
    ~Window();

public slots:
    void GiveRulesForGame();

private:
    Game* game;
    RenderArea* renderArea;
    QPushButton *playButton;
    QPushButton *stopButton;
    QPushButton *saveButton;
    QPushButton *loadButton;
    QPushButton *setRulesButton;
    QPushButton *setSizeButton;
    QLineEdit *modeLine;
    QLineEdit *widthLine;
    QLineEdit *heightLine;
    QLabel* modeLabel;
    QLabel* widthLabel;
    QLabel* heightLabel;
};
#endif
