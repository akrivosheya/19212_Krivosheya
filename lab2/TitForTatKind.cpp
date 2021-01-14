#include "TitForTatKind.h"
#include "Factory.h"

Strategy* createTitForTatKind();

namespace {
	bool g() {
		Factory<Strategy, std::string, Strategy* (*)()>::getInstance()->addCreator("titfortatkind", createTitForTatKind);
		return true;//у каждого класса
	}

	bool b = g();
}

void TitForTatKind::putDecisions(bool decision1, bool decision2) {
	betrayed = decision1 | decision2;
	return;
}

Strategy* createTitForTatKind() {
	return new TitForTatKind;
}
