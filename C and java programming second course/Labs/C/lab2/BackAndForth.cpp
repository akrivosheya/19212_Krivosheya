#include "BackAndForth.h"
#include "Factory.h"

Strategy* createBackAndForth();

namespace {
	bool g() {
		Factory<Strategy, std::string, Strategy* (*)()>::getInstance()->addCreator("backandforth", createBackAndForth);
		return true;//у каждого класса
	}

	bool b = g();
}

bool BackAndForth::makeDecision() {
	cORd = !cORd;
	return cORd;
}

Strategy* createBackAndForth() {
	return new BackAndForth;
}
