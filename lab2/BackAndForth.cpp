#include "BackAndForth.h"
#include "Factory.h"

namespace {
	bool g() {
		Factory<Strategy, std::string, Strategy* (*)()>::getInstance()->addCreator("backandforth", createBackAndForth);
		return true;//у каждого класса
	}

	bool b = g();
}

void BackAndForth::getRes(bool s1, bool s2) {
	return;
}

bool BackAndForth::makeMove() {
	cORd = !cORd;
	return cORd;
}


std::string BackAndForth::getName() {
	return name;
}

void BackAndForth::reload() {
	cORd = c;
}

Strategy* createBackAndForth() {
	return new BackAndForth;
}
