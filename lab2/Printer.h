#pragma once
#include "Strategy.h"
#include <vector>

class Printer {
public:
	Printer() = default;
	void PrintRes(Strategy* S1, Strategy* S2, Strategy* S3, 
		int pointS1, int pointS2, int pointS3);

	void PrintTournamentRes(std::vector<Strategy*>& strategys, std::vector<int>& victories);

	void PrintDetailedRes(bool moveS1, bool moveS2, bool moveS3,
		int pointS1, int pointS2, int pointS3,
		int getS1, int getS2, int getS3);
 };
