#pragma once
#include "Factory.h"
#include "Game.h"

class Preparation {
public:
	Game* Prepare(int& steps, std::string& mode, std::vector<Strategy*>& strategys, int& argc, char* argv[]);
private:
	bool IsMode(char* str);
	bool IsDigit(std::string str);
	void SetModeOptional(const int& size, std::string& mode);
	bool SetOptions(const int& size, std::string& mode, int& steps, int& i, const int& argc, char* argv[]);
	static constexpr int optionalSteps = 100;
};
