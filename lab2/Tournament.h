#include "Game.h"

class Tournament : public Game {
public:
	Tournament();
	void Play(Printer& print) override;
private:
	void Reload(Strategy* S1, Strategy* S2, Strategy* S3);
};

Game* createTournament() {
	return new Tournament();
}
