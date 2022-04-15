#ifndef TRANSLATER_H
#define TRANSLATER_H

#include <QObject>
#include <vector>

class Translater{
public:
    bool TranslateRules(const QString& rulesQS,
                        std::vector<std::vector<bool> >& newRules);
    bool TranslateSize(const QString& widthQS,
                       const QString& heightQS,
                       std::vector<std::vector<bool> >& matrix);

private:
    bool IsNumber(const QString& str);
    bool GetFirstRule(const QString& rulesStr,
                      const QChar* endOfFirstRule,
                      std::vector<std::vector<bool> >& newRules);
    bool GetSecondRule(const QString& rulesStr,
                       const QChar* endOfFirstRule,
                       std::vector<std::vector<bool> >& newRules);
    static constexpr int minRulesSize = 3;
    static constexpr int maxRulesSize = 19;
    static constexpr int maxNeighbours = 8;
    static constexpr int countOfRules = 2;
};

#endif // TRANSLATER_H
