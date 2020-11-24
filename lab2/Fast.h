#include "Game.h"

class Fast : public Game {
public:
	Fast();
	void Play(int& steps, std::vector<Strategy*>& strategys, const char* file) override;
};

Game* createFast();
