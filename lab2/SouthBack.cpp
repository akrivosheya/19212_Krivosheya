#include "SouthBack.h"
#include "Factory.h"
#include <iostream>

namespace {
	bool g() {
		Factory<Strategy, std::string, Strategy* (*)()>::getInstance()->addCreator("southback", createSouthBack);
		return true;//у каждого класса
	}

	bool b = g();
}

SouthBack::SouthBack() : 
	counter(0), 
	winner(false), 
	winnerIs(false),
	friendIs(true),
	master1(true), 
	master2(true),
	lastDecision(false){}

void SouthBack::putDecisions(bool decision1, bool decision2) {
	if (winnerIs) {
		return;
	}
	if (!friendIs) {
		BackAndForth::putDecisions(decision1, decision2);
		return;
	}
	if (counter < 10) {
		bool southDecision = (dancing & (mask << (counter - 1))) >> (counter - 1);
		if (decision1 != southDecision) {
			master1 = false;
		}
		if (decision2 != southDecision) {
			master2 = false;
		}
		if (!master1 && !master2) {
			friendIs = false;
		}
		return;
	}
	if (master1 || master2) {
		if (counter == 10) {
			++counter;
		}
		else {
			if (lastDecision > decision1) {
				master1 = false;
			}
			if (lastDecision > decision2) {
				master2 = false;
			}
			if ((master1 && (lastDecision < decision1)) || (master2 && (lastDecision < decision2))) {
				winnerIs = true;
			}
		}
		lastDecision = rand() % 2;
	}
	else {
		winner = winnerIs = true;
	}
}

bool SouthBack::makeDecision() {
	if (!friendIs) {
		return BackAndForth::makeDecision();
	}
	if (counter < 10) {
		++counter;
		return (dancing & (mask << (counter - 1))) >> (counter - 1);
	}
	if (!winnerIs) {
		return lastDecision;
	}
	if (winner) {
		return betray;
	}
	return help;
}

std::string SouthBack::getName() {
	return name;
}

void SouthBack::reload() {
	winnerIs = false;
	counter = 0;
	winner = false;
	friendIs = true;
	master1 = true;
	master2 = true;
}

Strategy* createSouthBack() {
	return new SouthBack();
}
