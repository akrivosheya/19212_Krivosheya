#include "Game.h"

class Tournament : public Game {
public:
	Tournament();
	void Play(int& steps, std::vector<Strategy*>& strategys, const char* file) override;
private:
	void Reload(Strategy* S1, Strategy* S2, Strategy* S3);
};

Game* createTournament();
