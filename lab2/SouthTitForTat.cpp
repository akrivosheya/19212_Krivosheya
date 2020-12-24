#pragma once
#include "SouthTitForTat.h"
#include "Factory.h"

namespace {
	bool g() {
		Factory<Strategy, std::string, Strategy* (*)()>::getInstance()->addCreator("southtitfortat", createSouthTitForTat);
		return true;//у каждого класса
	}

	bool b = g();
}

void SouthTitForTat::putDecisions(bool decision1, bool decision2) {
	if (thereIsWinner) {
		return;
	}
	if (!thereIsFriend) {
		TitForTatAnger::putDecisions(decision1, decision2);
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

bool SouthTitForTat::makeDecision() {
	if (!thereIsFriend) {
		return TitForTatAnger::makeDecision();
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

std::string SouthTitForTat::getName() {
	return name;
}

void SouthTitForTat::reload() {
	thereIsWinner = false;
	counter = 0;
	iAmWinner = false;
	thereIsFriend = true;
	firstIsFriend = true;
	secondIsFriend = true;
	lastDecision = false;
}
