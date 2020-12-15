#include "Game.h"
#include <cctype>
#include <cstdlib>

Game::Game(int width, int height, int rule1, int rule2, int rule3):
            matrix(height, std::vector<bool>(width)),
            rules{rule1, rule2, rule3},
            timerId(0),
            play(false),
            haveTimerId(false){}


void Game::timerEvent(QTimerEvent *event){
    if(!play){
        return;
    }
    std::vector<std::vector<bool> > copy = matrix;
    for(unsigned int i = 0; i < matrix.size(); ++i){
        for(unsigned int j = 0; j < matrix[0].size(); ++j){
            int count = 0;
            for(int k = -1; k < 2; ++k){
                for(int l = -1; l < 2; ++l){
                    if(((k == 0) && (l == 0)) ||
                            ((int)i + k < 0) || ((unsigned int)((int)i + k) >= matrix.size())
                            || ((int)j + l < 0) || ((unsigned int)((int)j + l) >= matrix[0].size()))
                    {
                        continue;
                    }
                    count += matrix[i + k][j + l];
                }
            }
            if(matrix[i][j] && ((count < rules[1]) || (count > rules[2]))){
                copy[i][j] = false;
            }
            else if(!matrix[i][j] && (count == rules[0])){
                copy[i][j] = true;
            }
        }
    }
    matrix = copy;
    emit Changed();
}


std::vector<std::vector<bool> >& Game::GetMatrix(){
    return matrix;
}

void Game::SetRules(QString qtRules){
    std::string rules = qtRules.toLocal8Bit().constData();
    if(rules.size() != rulesSize){
        return;
    }
    std::vector<int> newRules(3);
    if()
}


void Game::ChangeRect(int idx1, int idx2){
    if(!play && (unsigned int)idx1 < matrix.size()
            && (unsigned int)idx2 < matrix[0].size()){
        matrix[idx1][idx2] = !matrix[idx1][idx2];
        emit Changed();
    }
}

void Game::Activate(){
    play = true;
    timerId = startTimer(std::chrono::milliseconds(250));
    haveTimerId = true;
}

void Game::Diactivate(){
    play = false;
    if(haveTimerId){
        killTimer(timerId);
        haveTimerId = false;
    }
}

void Game::Resize(int width, int height){

}


