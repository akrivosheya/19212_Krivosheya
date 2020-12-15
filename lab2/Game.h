#pragma once
#include <string>
#include "Strategy.h"
#include "Printer.h"
#include <vector>
#include <fstream>

class Game {
public:
	Game();
	virtual ~Game();
	virtual void Play(const char* file, Printer& print){}
	void SetSteps(int& steps);
	void SetStrategys(std::vector<Strategy*>& strategys);
protected:
	std::string Decisions();
	void SetDecisions(Strategy* S1, Strategy* S2, Strategy* S3);
	void SetGets(const char* file);
	void SetPoints();
	void GiveDecisions(Strategy* S1, Strategy* S2, Strategy* S3);
	void SetWinners(int& S1, int& S2, int& S3);
	int steps;
	std::vector<Strategy*> strategys;
	bool decisionS1, decisionS2, decisionS3;
	int getS1, getS2, getS3;
	int pointS1, pointS2, pointS3;
	//для тестов
	std::string name;
	int tournamentCount;
	bool traitor1, traitor2, kind1, kind2, backandforth3, titfortat1;
};
