#ifndef DATAMASTER_H
#define DATAMASTER_H

#include <QObject>

class DataMaster: public QObject{
    Q_OBJECT;

public slots:
    void Save(std::vector<std::vector<bool> >& matrix, std::vector<int>& rules);
    void Load(std::vector<std::vector<bool> >& matrix, std::vector<int>& rules);
};

#endif // DATAMASTER_H
