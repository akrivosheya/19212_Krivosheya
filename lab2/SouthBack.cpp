#include "SouthBack.h"
#include "Factory.h"

Strategy* createSouthBack();

namespace {
	bool g() {
		Factory<Strategy, std::string, Strategy* (*)()>::getInstance()->addCreator("southback", createSouthBack);
		return true;//у каждого класса
	}

	bool b = g();
}

void SouthBack::putDecisions(bool decision1, bool decision2) {
	if (thereIsWinner) {
		return;
	}
	if (!thereIsFriend) {
		BackAndForth::putDecisions(decision1, decision2);
		return;
	}
	if (counter < 10) {
		bool southDecision = (dancing & (mask << (counter - 1))) >> (counter - 1);
		if (decision1 != southDecision) {
			firstIsFriend = false;
		}
		if (decision2 != southDecision) {
			secondIsFriend = false;
		}
		if (!firstIsFriend && !secondIsFriend) {
			thereIsFriend = false;
		}
		return;
	}
	if (firstIsFriend || secondIsFriend) {
		if (counter == 10) {
			++counter;
		}
		else {
			if (lastDecision > decision1) {
				firstIsFriend = false;
			}
			if (lastDecision > decision2) {
				secondIsFriend = false;
			}
			if ((firstIsFriend && (lastDecision < decision1)) || (secondIsFriend && (lastDecision < decision2))) {
				thereIsWinner = true;
			}
		}
		lastDecision = rand() % 2;
	}
	else {
		iAmWinner = thereIsWinner = true;
	}
}

bool SouthBack::makeDecision() {
	if (!thereIsFriend) {
		return BackAndForth::makeDecision();
	}
	if (counter < 10) {
		++counter;
		return (dancing & (mask << (counter - 1))) >> (counter - 1);
	}
	if (!thereIsWinner) {
		return lastDecision;
	}
	if (iAmWinner) {
		return betray;
	}
	return help;
}

void SouthBack::reload() {
	thereIsWinner = false;
	counter = 0;
	iAmWinner = false;
	thereIsFriend = true;
	firstIsFriend = true;
	secondIsFriend = true;
}

Strategy* createSouthBack() {
	return new SouthBack();
}
