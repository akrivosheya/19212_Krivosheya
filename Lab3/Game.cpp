#include "Game.h"

Game::Game(int width, int height):
    matrix(height, std::vector<bool>(width)),
    width(width),
    height(height),
    play(false){}

int Game::GetHeight(){
    return height;
}

int Game::GetWidth(){
    return width;
}
