#include "Traitor.h"
#include "Factory.h"

namespace {
	bool g() {
		Factory<Strategy, std::string, Strategy* (*)()>::getInstance()->addCreator("traitor", createTraitor);
		return true;//у каждого класса
	}
}

void Traitor::getRes(bool s1, bool s2) {
	return;
}

bool Traitor::makeMove() {
	return d;
}

Strategy* createTraitor() {
	return new Traitor;
}
