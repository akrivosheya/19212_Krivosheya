#pragma once
#include "Strategy.h"

class BackAndForth : public Strategy {
public:
	virtual ~BackAndForth() = default;
	void putDecisions(bool decision1, bool decision2) override {
		return;
	}
	bool makeDecision() override;
	std::string getName() override {
		return name;
	}
	void reload() override {
		cORd = help;
	}

private:
	bool cORd = help;
	std::string name = "BackAndForth";
};
