#include "Game.h"

class Tournament : public Game {
public:
	Tournament();
	void Play(const char* file, Printer& print) override;
private:
	void Reload(Strategy* S1, Strategy* S2, Strategy* S3);
};

Game* createTournament();
