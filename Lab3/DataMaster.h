#ifndef DATAMASTER_H
#define DATAMASTER_H

#include <QObject>
#include <iostream>

class DataMaster: public QObject{
    Q_OBJECT;

public slots:
    void Save(std::vector<std::vector<bool> >& matrix,
              std::vector<int>& rules);
    void Load(std::vector<std::vector<bool> >& matrix,
              std::vector<int>& rules);

private:
    bool GetVector(QDataStream& in, std::vector<int>& someVector, int limit);
    bool GetMatrix(QDataStream& in, std::vector<std::vector<bool> >& matrix);
    static constexpr int maxSize = 100;
    static constexpr int maxRule = 8;
};

#endif // DATAMASTER_H
