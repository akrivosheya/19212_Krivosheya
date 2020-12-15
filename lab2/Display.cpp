#include "pch.h"
#include "Display.h"

int Display::GetPoint(int i, Game* G) {
	switch (i) {
	case 1:
		return G->pointS1;
	case 2:
		return G->pointS2;
	case 3:
		return G->pointS3;
	}
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
	return G->tournamentCount;
}

bool Display::GetTraitor1(Game* G) {
	return G->traitor1;
}

bool Display::GetTraitor2(Game* G) {
	return G->traitor2;
}

bool Display::GetKind1(Game* G) {
	return G->kind1;
}

bool Display::GetKind2(Game* G) {
	return G->kind2;
}

bool Display::GetBackAndForth3(Game* G) {
	return G->backandforth3;
}

bool Display::GetTitForTat1(Game* G) {
	return G->titfortat1;
}
