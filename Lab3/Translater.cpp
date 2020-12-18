#include "Translater.h"

void Translater::TranslateRules(const QString& rulesQS){
    std::string rules = rulesQS.toLocal8Bit().constData();
    if(rules.size() != rulesSize){
        return;
    }
    std::vector<int> newRules(3);
    if(rules[0] == 'B' && rules[1] <= '8' && rules[1] >= '0'){
        newRules[0] = rules[1] - '0';
    }
    else{
        return;
    }
    if(rules[2] == '/' && rules[3] == 'S'
            && rules[4] >= '0' && rules[5] <= '8'
            && rules[4] <= rules[5]){
        newRules[1] = rules[4] - '0';
        newRules[2] = rules[5] - '0';
    }
    else{
        return;
    }

    emit TranslatedRules(newRules);
}

void Translater::TranslateSize(const QString& widthQS, const QString& heightQS){
    std::string widthStr = widthQS.toLocal8Bit().constData();
    std::string heightStr = heightQS.toLocal8Bit().constData();
    widthStr.erase( std::remove( widthStr.begin(), widthStr.end(), ' ' ), widthStr.end() );
    heightStr.erase( std::remove( heightStr.begin(), heightStr.end(), ' ' ), heightStr.end() );
    if(widthStr.size() > 3 || heightStr.size() > 3 ||
            widthStr.size() == 0 || heightStr.size() == 0 ||
            !IsNumber(widthStr) || !IsNumber(heightStr)){
        return;
    }
    int newWidth = stoi(widthStr);
    int newHeight = stoi(heightStr);
    if(newWidth == 0 || newHeight == 0 || newWidth > 100 || newHeight > 100){
        return;
    }
    std::vector<std::vector<bool> > newMatrix(newHeight, std::vector<bool>(newWidth));
    emit TranslatedSize(newMatrix);
}

bool Translater::IsNumber(const std::string& str){
    for(auto iter = str.begin(); iter !=str.end(); ++iter){
        if(!isdigit(*iter)){
            return false;
        }
    }
    return true;
}
