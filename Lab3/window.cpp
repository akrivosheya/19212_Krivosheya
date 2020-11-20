#include "window.h"

Window::Window()
{
    play_button = new QPushButton(tr("&Play"));
    stop_button = new QPushButton(tr("&Stop"));
    save_button = new QPushButton(tr("&Save"));
    load_button = new QPushButton(tr("&Load"));
    mode = new QLineEdit();
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(play_button, 0, 0);
    mainLayout->addWidget(stop_button, 0, 1);
    mainLayout->addWidget(save_button, 0, 2);
    mainLayout->addWidget(load_button, 0, 3);
    mainLayout->addWidget(mode, 0, 4);
    setLayout(mainLayout);
    setWindowTitle(tr("The Life"));
}

Window::~Window()
{
    delete play_button;
    delete stop_button;
    delete save_button;
    delete load_button;
    delete mode;
}

