#pragma once
#include "Factory.h"
#include "Game.h"

class Preparation {
public:
	Game* Prepare(int& argc, char* argv[]);
private:
	bool IsMode(char* str);
	bool IsDigit(std::string str);
	void SetModeOptional(int size, std::string& mode);
	bool SetOptions(int size, std::string& mode, int& steps, int i, int argc, char* argv[]);
	static constexpr int optionalSteps = 100;
};
