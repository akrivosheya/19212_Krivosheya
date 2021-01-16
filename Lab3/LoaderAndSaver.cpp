#include "LoaderAndSaver.h"

void LoaderAndSaver::SaveData(QDataStream& out,
                              std::vector<std::vector<bool> >& matrix,
                              std::vector<std::vector<bool> >& rules){
    for(auto iter = rules[0].begin(); iter != rules[0].end(); ++iter){
        out << (qint32)(*iter);
    }
    for(auto iter = rules[1].begin(); iter != rules[1].end(); ++iter){
        out << (qint32)(*iter);
    }
    out << (qint32)matrix[0].size() << (qint32)matrix.size();
    bool bitForWriting = matrix[0][0];
    int counter = 0;
    for(auto iter1 = matrix.begin(); iter1 != matrix.end(); ++iter1){
        for(auto iter2 = iter1->begin(); iter2 != iter1->end(); ++iter2){
            if(bitForWriting != *iter2){
                out << (qint32)counter << (qint32)bitForWriting;
                bitForWriting = *iter2;
                counter = 1;
            }
            else{
                ++counter;
            }
        }
    }
    out << (qint32)counter << (qint32)bitForWriting;
}


bool LoaderAndSaver::LoadData(QDataStream& in,
                              std::vector<std::vector<bool> >& matrix,
                              std::vector<std::vector<bool> >& rules){
    std::vector<std::vector<bool> > newRules(countOfRules,
                                             std::vector<bool>(maxNeighbours + 1));
    if(!GetRules(in, newRules)){
        return false;
    }
    std::vector<int> size(2);
    if(!GetSize(in, size, maxSize) ||
            size[0] == 0 || size[1] == 0){
        return false;
    }
    std::vector<std::vector<bool> > newMatrix(size[1], std::vector<bool>(size[0]));
    if(!GetMatrix(in, newMatrix)){
        return false;
    }
    rules = std::move(newRules);
    matrix = std::move(newMatrix);
    return true;
}

bool LoaderAndSaver::GetSize(QDataStream& in,
                             std::vector<int>& size,
                             int limit){
    for(auto iter = size.begin(); iter != size.end(); ++iter){
        in >> *iter;
        if(in.atEnd() || *iter <= 0 || *iter > limit){
            return false;
        }
    }
    return true;
}

bool LoaderAndSaver::GetMatrix(QDataStream& in,
                               std::vector<std::vector<bool> >& matrix){
    int counter = 0;
    int bitForLoading;
    for(auto iter1 = matrix.begin(); iter1 != matrix.end(); ++iter1){
        for(auto iter2 = iter1->begin(); iter2 != iter1->end(); ++iter2){
            if(!counter){
                if(in.atEnd()){
                    return true;
                }
                else{
                    in >> counter;
                }
                if(in.atEnd()){
                    return false;
                }
                else{
                    in >> bitForLoading;
                }
                if(bitForLoading > 1 || bitForLoading < 0){
                    return false;
                }
            }
            *iter2 = bitForLoading;
            --counter;
        }
    }
    return true;
}

bool LoaderAndSaver::GetRules(QDataStream& in,
                              std::vector<std::vector<bool> >& rules){
    int bitForLoading;
    for(auto iter1 = rules.begin(); iter1 != rules.end(); ++iter1){
        for(auto iter2 = iter1->begin(); iter2 != iter1->end(); ++iter2){
                in >> bitForLoading;
                if(bitForLoading > 1 || bitForLoading < 0){
                    return false;
                }
            *iter2 = bitForLoading;
        }
    }
    return true;
}

