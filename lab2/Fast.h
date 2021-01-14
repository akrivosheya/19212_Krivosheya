#pragma once
#include "Game.h"

class Fast : public Game {
public:
	Fast() {
		name = "Fast";
	}
	void Play(Printer& print) override;
};
