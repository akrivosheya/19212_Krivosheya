#ifndef DATAMASTER_H
#define DATAMASTER_H

#include "LoaderAndSaver.h"

class DataMaster{
public:
    int Save(std::vector<std::vector<bool> >& matrix,
             std::vector<std::vector<bool> >& rules,
             QString& error);
    int Load(std::vector<std::vector<bool> >& matrix,
             std::vector<std::vector<bool> >& rules,
             QString& error);
    int GetUnableCode(){
        return unableToOpen;
    }
    int GetFormatCode(){
        return wrongFormat;
    }
    int GetSuccessCode(){
        return success;
    }

private:
    static constexpr int success = 0;
    static constexpr int emptyName = 1;
    static constexpr int unableToOpen = 2;
    static constexpr int wrongFormat = 3;
    LoaderAndSaver helper;
};

#endif // DATAMASTER_H
