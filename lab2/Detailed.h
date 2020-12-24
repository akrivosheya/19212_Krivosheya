#include "Game.h"

class Detailed : public Game {
public:
	Detailed();
	void Play(Printer& print) override;
};

Game* createDetailed() {
	return new Detailed();
}
