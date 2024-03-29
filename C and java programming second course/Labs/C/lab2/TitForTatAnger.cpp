#include "TitForTatAnger.h"
#include "Factory.h"

Strategy* createTitForTatAnger();

namespace {
	bool g() {
		Factory<Strategy, std::string, Strategy* (*)()>::getInstance()->addCreator("titfortatanger", createTitForTatAnger);
		return true;//у каждого класса
	}

	bool b = g();
}

void TitForTatAnger::putDecisions(bool decision1, bool decision2) {
	betrayed = decision1 & decision2;
	return;
}

Strategy* createTitForTatAnger() {
	return new TitForTatAnger;
}
