#pragma once
#include <string>
#include "Strategy.h"
#include <vector>
#include <fstream>

class Game {
public:
	virtual void Play(int& steps, std::vector<Strategy*>& strategys, const char* file) = 0;
	int GetPoint(int i);
	virtual ~Game() {}
protected:
	std::string Moves(bool& moveS1, bool& moveS2, bool& moveS3);
	void GetMoves(bool& moveS1, bool& moveS2, bool& moveS3, Strategy* S1, Strategy* S2, Strategy* S3);
	void GetGets(bool& moveS1, bool& moveS2, bool& moveS3, int& getS1, int& getS2, int& getS3);
	void GetPoints(int& pointS1, int& pointS2, int& pointS3, int& getS1, int& getS2, int& getS3);
	void PutRes(bool& moveS1, bool& moveS2, bool& moveS3, Strategy* S1, Strategy* S2, Strategy* S3);
	void PrintRes(int& pointS1, int& pointS2, int& pointS3, Strategy* S1, Strategy* S2, Strategy* S3);
	void SetWinners(int& pointS1, int& pointS2, int& pointS3, int& S1, int& S2, int& S3);
	std::string GetName();
	int pointS1, pointS2, pointS3;
	std::string name;
};
