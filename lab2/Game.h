#pragma once
#include <string>
#include "Strategy.h"
#include <vector>
#include <fstream>

class Game {
public:
	Game();
	virtual ~Game() {}
	virtual void Play(int& steps, std::vector<Strategy*>& strategys, const char* file) = 0;
	int GetPoint(int i);
	std::string GetName();
	
	int countTournament;
	bool moveSouth1, moveSouth2, moveSTFT1, moveBack, moveKind, moveTraitor, moveTK, moveTA;
protected:
	std::string Moves();
	void GetMoves(Strategy* S1, Strategy* S2, Strategy* S3);
	void GetGets();
	void GetPoints();
	void PutRes(Strategy* S1, Strategy* S2, Strategy* S3);
	void PrintRes(Strategy* S1, Strategy* S2, Strategy* S3);
	void SetWinners(int& S1, int& S2, int& S3);
	bool moveS1, moveS2, moveS3;
	int getS1, getS2, getS3;
	int pointS1, pointS2, pointS3;
	std::string name;
};
