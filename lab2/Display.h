#pragma once
#include "Game.h"
#include <vector>
#include "Strategy.h"

class Display {
public:
	std::vector<int>& GetPoint(Game* G);
	int GetSteps(Game* G);
	bool GetTraitor1(Game* G);
	bool GetTraitor2(Game* G);
	bool GetKind1(Game* G);
	bool GetKind2(Game* G);
	bool GetBackAndForth3(Game* G);
	bool GetTitForTat1(Game* G);
	int GetTournamentCount(Game* G);
	std::vector<Strategy*>& GetStrategys(Game* G);
	std::string GetName(Game* G);
};
