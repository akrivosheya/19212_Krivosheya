#pragma once
#include "Strategy.h"

class Kind : public Strategy {
public:
	void putDecisions(bool decision1, bool decision2) override{
		return;
	}
	bool makeDecision() override{
		return help;
	}
	std::string getName() override{
		return name;
	}
	void reload() override {};
private:
	std::string name = "Kind";
};
