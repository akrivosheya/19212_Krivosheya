#pragma once
#include "Game.h"

class Detailed : public Game {
public:
	Detailed() {
		name = "Detailed";
	}
	void Play(Printer& print) override;
};
