#pragma once
#include "Strategy.h"

class Traitor : public Strategy {
public:
	void putDecisions(bool decision1, bool decision2) override {}
	bool makeDecision() override {
		return betray;
	}
	std::string getName() override{
		return name;
	}
	void reload() override {};

private:
	std::string name = "Traitor";
};
