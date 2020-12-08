#pragma once
#include <string>
#include "Strategy.h"
#include "Printer.h"
#include <vector>
#include <fstream>

class Game {
public:
	Game();
	virtual ~Game() {}
	virtual void Play(const char* file, Printer& print){}
	int GetPoint(int i);
	std::string GetName();
	void SetSteps(int& steps);
	void SetStrategys(std::vector<Strategy*>& strategys);
protected:
	std::string Moves();
	void GetMoves(Strategy* S1, Strategy* S2, Strategy* S3);
	void GetGets(const char* file);
	void GetPoints();
	void PutRes(Strategy* S1, Strategy* S2, Strategy* S3);
	void SetWinners(int& S1, int& S2, int& S3);
	int steps;
	std::vector<Strategy*> strategys;
	bool moveS1, moveS2, moveS3;
	int getS1, getS2, getS3;
	int pointS1, pointS2, pointS3;
	std::string name;
};
