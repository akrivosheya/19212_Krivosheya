#pragma once
#include "Game.h"

class Launcher {
public:
	Launcher();
	~Launcher() = default;
	int Launch(int argc, char* argv[], std::string& mode, int& steps, std::vector<Strategy*>& strategys);
	int GetCount();
	bool GetSouth1();
	bool GetSouth2();
	bool GetSTFT1();
	bool GetBack();
	bool GetKind();
	bool GetTraitor();
	bool GetTK();
	bool GetTA();
	int GetPoint(int i);
private:
	int countTournament;
	int pointS1, pointS2, pointS3;
	bool moveSouth1, moveSouth2, moveSTFT1, moveBack, moveKind, moveTraitor, moveTK, moveTA;
	std::string nameOfGame;
};
