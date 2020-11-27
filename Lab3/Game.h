#ifndef GAME_H
#define GAME_H

#include <vector>

class Game{
public:
    Game(int width = 25, int height = 25);
    std::vector<std::vector<bool> >GetMatrix();
    int GetHeight();
    int GetWidth();
private:
    std::vector<std::vector<bool> > matrix;
    int width;
    int height;
    bool play;
};

#endif // GAME_H
