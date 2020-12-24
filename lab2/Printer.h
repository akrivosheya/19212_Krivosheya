#pragma once
#include <vector>
#include <iostream>

#include "Strategy.h"

class Printer {
public:
	Printer() = default;
	void PrintRes(std::vector<Strategy*>& strategys, 
		std::vector<int> points, int i, int j, int k);

	void PrintTournamentRes(std::vector<Strategy*>& strategys, 
				std::vector<int>& victories);

	void PrintDetailedRes(std::vector<bool> decisions, 
			      std::vector<int> gets, std::vector<int> points);
 };
