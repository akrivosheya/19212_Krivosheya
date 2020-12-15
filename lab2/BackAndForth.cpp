#include "BackAndForth.h"
#include "Factory.h"

namespace {
	bool g() {
		Factory<Strategy, std::string, Strategy* (*)()>::getInstance()->addCreator("backandforth", createBackAndForth);
		return true;//у каждого класса
	}

	bool b = g();
}

void BackAndForth::putDecisions(bool decision1, bool decision2) {
	return;
}

bool BackAndForth::makeDecision() {
	cORd = !cORd;
	return cORd;
}


std::string BackAndForth::getName() {
	return name;
}

void BackAndForth::reload() {
	cORd = help;
}

Strategy* createBackAndForth() {
	return new BackAndForth;
}
