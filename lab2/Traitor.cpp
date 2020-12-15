#include "Traitor.h"
#include "Factory.h"

namespace {
	bool g() {
		Factory<Strategy, std::string, Strategy* (*)()>::getInstance()->addCreator("traitor", createTraitor);
		return true;//у каждого класса
	}

	bool b = g();
}

void Traitor::putDecisions(bool decision1, bool decision2) {
	return;
}

bool Traitor::makeDecision() {
	return betray;
}

std::string Traitor::getName() {
	return name;
}

Strategy* createTraitor() {
	return new Traitor;
}
