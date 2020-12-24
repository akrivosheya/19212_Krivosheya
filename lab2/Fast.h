#include "Game.h"

class Fast : public Game {
public:
	Fast();
	void Play(Printer& print) override;
};

Game* createFast() {
	return new Fast();
}
