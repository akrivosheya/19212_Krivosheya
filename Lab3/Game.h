#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <vector>

class Game: public QObject{
    Q_OBJECT
public:
    Game(int width = defaultSize, int height = defaultSize,
         int rule1 = defaultRuleOfLife,
         int rule2 = defaultRuleOfDeathMin,
         int rule3 = defaultRuleOfDeathMax);
    std::vector<std::vector<bool> >& GetMatrix();
    bool GetPlay();
    std::vector<int>& GetRules();

public slots:
    void SetRules(std::vector<int>& newRules);
    void Resize(std::vector<std::vector<bool> >& newMatrix);
    void ChangeRect(int idx1, int idx2);
    void Activate();
    void Diactivate();
    void Clear();

signals:
    void Changed();

private:
    void timerEvent(QTimerEvent *event) override;
    bool IsNumber(const std::string& str);
    static constexpr int defaultSize = 25;
    enum defaultRules{ defaultRuleOfLife = 3,
                       defaultRuleOfDeathMin = 2,
                       defaultRuleOfDeathMax = 3};
    std::vector<std::vector<bool> > matrix;
    std::vector<int> rules;
    int timerId = 0;
    bool play = false;
};

#endif // GAME_H
