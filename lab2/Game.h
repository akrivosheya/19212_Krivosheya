#pragma once
#include <vector>
#include <fstream>
#include <string>

#include "Strategy.h"
#include "Printer.h"

class Game {
public:
	Game();
	virtual ~Game();
	virtual void Play(Printer& print){}
	void SetSteps(int steps);
	void SetStrategys(std::vector<Strategy*>&& strategys);
	void SetRules(std::ifstream& is);
protected:
	void SetDecisions(Strategy* S1, Strategy* S2, Strategy* S3);
	void SetGets();
	void SetPoints();
	void GiveDecisions(Strategy* S1, Strategy* S2, Strategy* S3);
	void SetWinners(int& S1, int& S2, int& S3);
	int steps = 0;
	std::vector<Strategy*> strategys;
	std::vector<bool> decisions;
	std::vector<int> gets;
	std::vector<int> points;
	std::vector<int> rules;
	//для тестов
	std::string name;
	int tournamentCountForTest = 0;
	bool traitor1ForTest = true, traitor2ForTest = true;
	bool kind1ForTest = true, kind2ForTest = true;
	bool backandforth3ForTest = true, titfortat1ForTest = true;
};
