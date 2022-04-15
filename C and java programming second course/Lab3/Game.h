#ifndef GAME_H
#define GAME_H

#include <vector>

class Game{
public:
    Game(int width = defaultSize, int height = defaultSize);
    std::vector<std::vector<bool> >& GetMatrix(){
        return matrix;
    }
    bool GetIsPlaying(){
        return isPlaying;
    }
    std::vector<std::vector<bool> >& GetRules(){
        return rules;
    }
    void SetRules(std::vector<std::vector<bool> >& newRules){
        rules = std::move(newRules);
    }
    void Resize(std::vector<std::vector<bool> >& newMatrix){
        matrix = std::move(newMatrix);
    }
    void ChangeRect(int idx1, int idx2);
    void Activate(){
        isPlaying = true;
    }
    void Diactivate(){
        isPlaying = false;
    }
    void Clear();
    void MakeStep();

private:
    static constexpr int defaultSize = 25;
    enum defaultRules{ maxNeighbours = 8,
                       countOfRules = 2,
                       defaultRuleOfLife = 3,
                       defaultRuleOfDeathMin = 2,
                       defaultRuleOfDeathMax = 3};
    std::vector<std::vector<bool> > matrix;
    std::vector<std::vector<bool> > rules;
    bool isPlaying = false;
};

#endif // GAME_H
