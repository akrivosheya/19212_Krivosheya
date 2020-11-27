#include "RenderArea.h"

RenderArea::RenderArea(): pressedX(0), pressedY(0){}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(500, 500);
}

void RenderArea::mousePressEvent(QMouseEvent* event){ 
    pressedX = event->x();
    pressedY = event->y();
}

int RenderArea::GetX(){
    return pressedX;
}

int RenderArea::GetY(){
    return pressedY;
}

void RenderArea::paintEvent(QPaintEvent*){
    QRect rect(0, 0, width() - 1, height() - 1);
    QPainter painter(this);
    painter.setBrush(Qt::gray);
    painter.setPen(Qt::darkGreen);
    painter.drawRect(rect);
    for (int i = 20; i < width(); i += 20){
        painter.drawLine(i, 0, i, height());
    }
    for (int i = 20; i < height(); i += 20){
        painter.drawLine(0, i, width(), i);
    }
}
