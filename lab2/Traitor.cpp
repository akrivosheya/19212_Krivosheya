#include "Traitor.h"
#include "Factory.h"

namespace {
	bool g() {
		Factory<Strategy, std::string, Strategy* (*)()>::getInstance()->addCreator("traitor", createTraitor);
		return true;//у каждого класса
	}

	bool b = g();
}

void Traitor::getRes(bool s1, bool s2) {
	return;
}

bool Traitor::makeMove() {
	return d;
}

std::string Traitor::getName() {
	return name;
}

Strategy* createTraitor() {
	return new Traitor;
}
