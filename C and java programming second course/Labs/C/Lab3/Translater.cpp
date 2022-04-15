#include <algorithm>

#include "Translater.h"

bool Translater::TranslateRules(const QString& rulesStr,
                                std::vector<std::vector<bool> >& rules){
    if(!(rulesStr.size() >= minRulesSize && rulesStr.size() <= maxRulesSize)){
        return false;
    }
    const QChar* endOfFirstRule = std::find(rulesStr.begin(), rulesStr.end(), '/');
    std::vector<std::vector<bool> > newRules(countOfRules, std::vector<bool>(maxNeighbours + 1));
    if(!GetFirstRule(rulesStr, endOfFirstRule, newRules)){
        return false;
    }
    if(!GetSecondRule(rulesStr, endOfFirstRule, newRules)){
        return false;
    }
    rules = std::move(newRules);
    return true;
}

bool Translater::TranslateSize(const QString& widthStr,
                               const QString& heightStr,
                               std::vector<std::vector<bool> >& matrix){
    if(widthStr.size() > 3 || heightStr.size() > 3 ||
            widthStr.size() == 0 || heightStr.size() == 0 ||
            !IsNumber(widthStr) || !IsNumber(heightStr)){
        return false;
    }
    int newWidth = widthStr.toInt();
    int newHeight = heightStr.toInt();
    if(newWidth == 0 || newHeight == 0 || newWidth > 100 || newHeight > 100){
        return false;
    }
    std::vector<std::vector<bool> > newMatrix(newHeight, std::vector<bool>(newWidth));
    matrix = std::move(newMatrix);
    return true;
}

bool Translater::IsNumber(const QString& str){
    return str.end() == std::find_if(str.begin(),
                                     str.end(),
                                     [](QChar c)-> bool {return !c.isDigit();});
}

bool Translater::GetFirstRule(const QString& rulesStr,
                              const QChar* endOfFirstRule,
                              std::vector<std::vector<bool> >& newRules){
    if(rulesStr[0] == 'B' && rulesStr[1].isDigit()){
        if((endOfFirstRule - rulesStr.begin() - 1) > maxNeighbours ||
                rulesStr.end() == endOfFirstRule){
            return false;
        }
        int lastDigit = -1;
        for(auto iter = rulesStr.begin() + 1;
            iter != endOfFirstRule; ++iter){
            if(iter->isDigit() &&
                    lastDigit < iter->digitValue() &&
                    iter->digitValue() <= maxNeighbours){
                newRules[0][iter->digitValue()] = true;
                lastDigit = iter->digitValue();
            }
            else{
                return false;
            }
        }
    }
    else{
        return false;
    }
    return true;
}

bool Translater::GetSecondRule(const QString& rulesStr,
                               const QChar* endOfFirstRule,
                               std::vector<std::vector<bool> >& newRules){
    if(endOfFirstRule + 1 != rulesStr.end() &&
            endOfFirstRule + 2 != rulesStr.end()&&
            *(endOfFirstRule + 1) == 'S' &&
            (endOfFirstRule + 2)->isDigit()){
        if((rulesStr.end() - endOfFirstRule - 2) > maxNeighbours){
            return false;
        }
        int lastDigit = -1;
        for(auto iter = endOfFirstRule + 2;
            iter != rulesStr.end(); ++iter){
            if(iter->isDigit() &&
                    lastDigit < iter->digitValue() &&
                    iter->digitValue() <= maxNeighbours){
                newRules[1][iter->digitValue()] = true;
                lastDigit = iter->digitValue();
            }
            else{
                return false;
            }
        }
    }
    else{
        return false;
    }
    return true;
}
