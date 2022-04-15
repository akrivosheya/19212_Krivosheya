#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPen>
#include <QPainter>
#include <QMouseEvent>
#include <vector>

#include "Game.h"

class RenderArea: public QWidget{
    Q_OBJECT
public:
    RenderArea(Game* game_):
        game(game_){
    }
    QSize minimumSizeHint() const override{
        return QSize(500, 500);
    }
    void mousePressEvent(QMouseEvent* event) override;

public slots:
    void Update(){
        update();
    }

signals:
    void Clicked(int idx1, int idx2);

private:
    void paintEvent(QPaintEvent *event) override;
    Game* game;
    int rectWidth;
    int rectHeight;
};

#endif // RENDERAREA_H


