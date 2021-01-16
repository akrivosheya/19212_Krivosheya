#include <cctype>
#include <cstdlib>
#include <algorithm>

#include "Game.h"

Game::Game(int width, int height):
           matrix(height, std::vector<bool>(width)),
           rules(countOfRules, std::vector<bool>(maxNeighbours + 1)){
    rules[0][defaultRuleOfLife] = true;
    rules[1][defaultRuleOfDeathMin] = true;
    rules[1][defaultRuleOfDeathMax] = true;
}

void Game::MakeStep(){
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
            if(matrix[i][j] && !rules[1][count]){
                copy[i][j] = false;
            }
            else if(!matrix[i][j] && rules[0][count]){
                copy[i][j] = true;
            }
        }
    }
    matrix = copy;
}

void Game::ChangeRect(int idx1, int idx2){
    if(!isPlaying && (unsigned int)idx1 < matrix.size()
            && (unsigned int)idx2 < matrix[0].size()){
        matrix[idx1][idx2] = !matrix[idx1][idx2];
    }
}

void Game::Clear(){
    for(auto iter = matrix.begin(); iter != matrix.end(); ++iter){
        std::fill(iter->begin(), iter->end(), 0);
    }
}


