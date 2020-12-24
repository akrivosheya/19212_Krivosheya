#pragma once
#include "Strategy.h"
#include "BackAndForth.h"

class SouthBack : public BackAndForth {
public:
	SouthBack() = default;
	void putDecisions(bool decision1, bool decision2) override;
	bool makeDecision() override;
	std::string getName() override;
	void reload() override;
private:
	static constexpr int dancing = 618;
	static constexpr int mask = 1;
	std::string name = "SouthBack";
	int counter = 0;
	bool iAmWinner = false;
	bool thereIsWinner = false;
	bool thereIsFriend = true;
	bool firstIsFriend = true;
	bool secondIsFriend = true;
	bool lastDecision = false;
};

Strategy* createSouthBack() {
	return new SouthBack();
}
