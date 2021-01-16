#ifndef TIMER_H
#define TIMER_H

#include <QObject>

class Timer: public QObject
{
    Q_OBJECT

public:
    void KillTimer(){
        killTimer(timerId);
    }
    void StartTimer(){
        timerId = startTimer(std::chrono::milliseconds(250));
    }

signals:
    void TimeIsUp();

private:
    void timerEvent(QTimerEvent *event) override{
        emit TimeIsUp();
    }
    int timerId = 0;
};

#endif // TIMER_H
