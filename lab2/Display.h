#pragma once
#include <vector>

#include "Game.h"
#include "Strategy.h"

class Display {
public:
	std::vector<int>& GetPoint(Game* G) {
		return G->points;
	}
	std::string GetName(Game* G) {
		return G->name;
	}
	int GetSteps(Game* G) {
		return G->steps;
	}
	std::vector<std::unique_ptr<Strategy> >& GetStrategys(Game* G) {
		return G->strategys;
	}
	int GetTournamentCount(Game* G) {
		return G->tournamentCountForTest;
	}
	bool GetTraitor1(Game* G) {
		return G->traitor1ForTest;
	}
	bool GetTraitor2(Game* G) {
		return G->traitor2ForTest;
	}
	bool GetKind1(Game* G) {
		return G->kind1ForTest;
	}
	bool GetKind2(Game* G) {
		return G->kind2ForTest;
	}
	bool GetBackAndForth3(Game* G) {
		return G->backandforth3ForTest;
	}
	bool GetTitForTat1(Game* G) {
		return G->titfortat1ForTest;
	}
};
