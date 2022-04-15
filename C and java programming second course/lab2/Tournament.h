#pragma once
#include "Game.h"

class Tournament : public Game {
public:
	Tournament() {
		name = "Tournament";
	}
	void Play(Printer& print) override;
private:
	void Reload(Strategy* S1, Strategy* S2, Strategy* S3);
};
