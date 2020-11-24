#include "Game.h"

class Detailed : public Game {
public:
	Detailed();
	void Play(int& steps, std::vector<Strategy*>& strategys, const char* file) override;
};

Game* createDetailed();
