#include "RenderArea.h"

RenderArea::RenderArea(std::vector<std::vector<bool> >& matrix_):
    matrix(matrix_){
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(500, 500);
}


void RenderArea::Update(){
    update();
}

void RenderArea::mousePressEvent(QMouseEvent* event){
    int idx1 = (int)event->y() / rectHeight;
    int idx2 = (int)event->x() / rectWidth;
    emit Clicked(idx1, idx2);
}

void RenderArea::paintEvent(QPaintEvent*){
    rectHeight = (int)height() / matrix.size();
    rectWidth = (int)width() / matrix[0].size();
    QRect rect(0, 0, rectWidth * matrix[0].size(), rectHeight * matrix.size());
    QPainter painter(this);
    painter.setBrush(Qt::gray);
    painter.setPen(Qt::darkGreen);
    painter.drawRect(rect);
    for (int i = rectWidth; i < width(); i += rectWidth){
        painter.drawLine(i, 0, i, rectHeight * matrix.size());
    }
    for (int i = rectHeight; i < height(); i += rectHeight){
        painter.drawLine(0, i, rectWidth * matrix[0].size(), i);
    }
    painter.setBrush(Qt::cyan);
    for(unsigned int i = 0; i < matrix.size(); ++i){
        for(unsigned int j = 0; j < matrix[0].size(); ++j){
            if(matrix[i][j]){
                painter.drawRect(j * rectWidth, i * rectHeight,
                                 rectWidth, rectHeight);
            }
        }
    }
}
