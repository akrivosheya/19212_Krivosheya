#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include "RenderArea.h"
#include "Game.h"

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();
    ~Window();
    
public slots:
    void changeRect();

private:
    Game* game;
    RenderArea* renderArea;
    QPushButton *play_button;
    QPushButton *stop_button;
    QPushButton *save_button;
    QPushButton *load_button;
    QLineEdit *mode;
};
#endif
