#include "RenderArea.h"

void RenderArea::mousePressEvent(QMouseEvent* event){
    int idx1 = (int)event->y() / rectHeight;
    int idx2 = (int)event->x() / rectWidth;
    emit Clicked(idx1, idx2);
}

void RenderArea::paintEvent(QPaintEvent*){
    rectHeight = (int)height() / game->GetMatrix().size();
    rectWidth = (int)width() / game->GetMatrix()[0].size();
    QRect rect(0, 0,
               rectWidth * game->GetMatrix()[0].size(),
               rectHeight * game->GetMatrix().size());
    QPainter painter(this);
    painter.setBrush(Qt::gray);
    painter.setPen(Qt::darkGreen);
    painter.drawRect(rect);
    for (int i = rectWidth; i < width(); i += rectWidth){
        painter.drawLine(i, 0, i, rectHeight * game->GetMatrix().size());
    }
    for (int i = rectHeight; i < height(); i += rectHeight){
        painter.drawLine(0, i, rectWidth * game->GetMatrix()[0].size(), i);
    }
    painter.setBrush(Qt::cyan);
    for(unsigned int i = 0; i < game->GetMatrix().size(); ++i){
        for(unsigned int j = 0; j < game->GetMatrix()[0].size(); ++j){
            if(game->GetMatrix()[i][j]){
                painter.drawRect(j * rectWidth, i * rectHeight,
                                 rectWidth, rectHeight);
            }
        }
    }
}
