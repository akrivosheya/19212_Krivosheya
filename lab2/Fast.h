#include "Game.h"

class Fast : public Game {
public:
	Fast();
	void Play(const char* file, Printer& print) override;
};

Game* createFast();
