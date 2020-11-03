#include "Southampton.h"
#include "Factory.h"

namespace {
	bool g() {
		Factory<Strategy, std::string, Strategy* (*)()>::getInstance()->addCreator("southampton", createSouthampton);
		return true;//у каждого класса
	}

	bool b = g();
}

bool Southampton::winnerIs = false;

Southampton::Southampton() : counter(0), winner(true), s1(true), s2(true) {
	if (winnerIs) {
		winner = false;
		return;
	}
	winnerIs = true;
}

void Southampton::getRes(bool s1, bool s2) {
	if (!winnerIs) {
		winner = true;
		winnerIs = true;
	}
	if (winner) {
		return;
	}
	if (counter <= 10) {
		bool move = (dancing & (mask << (counter - 1))) >> (counter - 1);
		if (this->s1) {
			if (s1 != move) {
				this->s1 = false;
			}
		}
		if (this->s2) {
			if (s2 != move) {
				this->s2 = false;
			}
		}
	}
}

bool Southampton::makeMove() {
	if (counter < 10) {
		++counter;
		return dancing & (mask << (counter - 1));
	}
	if (winner) {
		return d;
	}
	if (this->s1 || this->s2) {
		return c;
	}
	return d;
}

std::string Southampton::getName() {
	return name;
}

void Southampton::reload() {
	winnerIs = false;
	counter = 0;
	winner = false;
	s1 = true;
	s2 = true;
}

Strategy* createSouthampton() {
	return new Southampton;
}
