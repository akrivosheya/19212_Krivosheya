#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <vector>

class Game: public QObject{
    Q_OBJECT
public:
    Game(int width = defaultSize, int height = defaultSize,
         int rule1 = defaultRule1, int rule2 = defaultRule2, int rule3 = defaultRule3);
    std::vector<std::vector<bool> >& GetMatrix();
    void SetRules(QString);

public slots:
    void ChangeRect(int idx1, int idx2);
    void Activate();
    void Diactivate();
    void Resize(int width, int height);

signals:
    void Changed();

private:
    void timerEvent(QTimerEvent *event) override;
    static constexpr int defaultSize = 25;
    static constexpr int defaultRule1 = 3;
    static constexpr int defaultRule2 = 2;
    static constexpr int defaultRule3 = 3;
    static constexpr int rulesSize = 5;
    std::vector<std::vector<bool> > matrix;
    std::vector<int> rules;
    int timerId;
    bool play, haveTimerId;
};

#endif // GAME_H
