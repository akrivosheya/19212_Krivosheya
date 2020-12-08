#include "Game.h"

class Detailed : public Game {
public:
	Detailed();
	void Play(const char* file, Printer& print) override;
};

Game* createDetailed();
