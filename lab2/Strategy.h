#pragma once
#include <iostream>

class Strategy {
public:
	virtual ~Strategy() {}
	virtual void putDecisions(bool decision1, bool decision2) = 0;
	virtual bool makeDecision() = 0;
	virtual std::string getName() = 0;
	virtual void reload() = 0;
protected:
	static constexpr bool help = true;
	static constexpr bool betray = false;
};
