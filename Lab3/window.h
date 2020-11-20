#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();
    ~Window();

private:
    QPushButton *play_button;
    QPushButton *stop_button;
    QPushButton *save_button;
    QPushButton *load_button;
    QLineEdit *mode;
};
#endif
