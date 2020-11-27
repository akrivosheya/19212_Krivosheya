#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPen>
#include <QPainter>
#include <QMouseEvent>

class RenderArea: public QWidget{
public:
    explicit RenderArea();
    QSize minimumSizeHint() const override;
    int GetX();
    int GetY();
    void mousePressEvent(QMouseEvent* event) override;
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    int pressedX;
    int pressedY;
};

#endif // RENDERAREA_H


