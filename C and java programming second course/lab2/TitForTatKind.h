#pragma once
#include "Strategy.h"

class TitForTatKind : public Strategy {
public:
	void putDecisions(bool decision1, bool decision2) override;
	bool makeDecision() override {
		return betrayed;
	}
	std::string getName() override {
		return name;
	}
	void reload() override {
		betrayed = false;
	}
private:
	bool betrayed = false;
	std::string name = "TitForTatKind";
};
