#include "TitForTatAnger.h"
#include "Factory.h"

namespace {
	bool g() {
		Factory<Strategy, std::string, Strategy* (*)()>::getInstance()->addCreator("titfortatanger", createTitForTatAnger);
		return true;//у каждого класса
	}
	
	bool b = g();
}

void TitForTatAnger::getRes(bool s1, bool s2) {
	betrayed = s1 & s2;
	return;
}

bool TitForTatAnger::makeMove() {
	return betrayed;
}

Strategy* createTitForTatAnger() {
	return new TitForTatAnger;
}
