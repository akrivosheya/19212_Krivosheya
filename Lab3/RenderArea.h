#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPen>
#include <QPainter>
#include <QMouseEvent>
#include <vector>

class RenderArea: public QWidget{
    Q_OBJECT
public:
    RenderArea(std::vector<std::vector<bool> >& matrix_);
    QSize minimumSizeHint() const override;
    void mousePressEvent(QMouseEvent* event) override;

public slots:
    void Update();

signals:
    void Clicked(int idx1, int idx2);

private:
    void paintEvent(QPaintEvent *event) override;
    std::vector<std::vector<bool> >& matrix;
    int rectWidth;
    int rectHeight;
};

#endif // RENDERAREA_H


