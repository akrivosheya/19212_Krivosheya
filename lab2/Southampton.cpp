#include "Southampton.h"
#include "Factory.h"

namespace {
	bool g() {
		Factory<Strategy, std::string, Strategy* (*)()>::getInstance()->addCreator("southampton", createSouthampton);
		return true;//у каждого класса
	}
}

bool Southampton::winnerIs = false;

void Southampton::getRes(bool s1, bool s2) {
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

Strategy* createSouthampton() {
	return new Southampton;
}
