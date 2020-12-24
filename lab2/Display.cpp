#include "Display.h"

std::vector<int>& Display::GetPoint(Game* G) {
	return G->points;
}

std::string Display::GetName(Game* G) {
	return G->name;
}


int Display::GetSteps(Game* G) {
	return G->steps;
}

std::vector<Strategy*>& Display::GetStrategys(Game* G) {
	return G->strategys;
}

int Display::GetTournamentCount(Game* G) {
	return G->tournamentCountForTest;
}

bool Display::GetTraitor1(Game* G) {
	return G->traitor1ForTest;
}

bool Display::GetTraitor2(Game* G) {
	return G->traitor2ForTest;
}

bool Display::GetKind1(Game* G) {
	return G->kind1ForTest;
}

bool Display::GetKind2(Game* G) {
	return G->kind2ForTest;
}

bool Display::GetBackAndForth3(Game* G) {
	return G->backandforth3ForTest;
}

bool Display::GetTitForTat1(Game* G) {
	return G->titfortat1ForTest;
}
