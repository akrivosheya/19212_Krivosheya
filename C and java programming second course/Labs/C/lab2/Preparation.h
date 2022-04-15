#pragma once
#include "Factory.h"
#include "Game.h"

class Preparation {
public:
	Game* Prepare(int& argc, char* argv[]);
private:
	bool IsMode(const std::string & str) {
		return !(strcmp(str.c_str(), "detailed") && strcmp(str.c_str(), "fast") && strcmp(str.c_str(), "tournament"));
	}
	bool IsDigit(std::string str);
	void SetModeOptional(int size, std::string& mode);
	bool SetOptions(int size, std::string& mode, int& steps, int i, int argc, char* argv[]);
	static constexpr int optionalSteps = 100;
};
