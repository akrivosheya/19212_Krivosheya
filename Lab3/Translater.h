#ifndef TRANSLATER_H
#define TRANSLATER_H

#include <QObject>

class Translater: public QObject{
    Q_OBJECT;


public:
    void TranslateRules(const QString& rulesQS);
    void TranslateSize(const QString& widthQS, const QString& heightQS);

signals:
    void TranslatedRules(std::vector<int>& newRules);
    void TranslatedSize(std::vector<std::vector<bool> >& newMatrix);

private:
    bool IsNumber(const std::string& str);
    static constexpr int rulesSize = 6;
};

#endif // TRANSLATER_H
