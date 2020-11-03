#include "TitForTatKind.h"
#include "Factory.h"

namespace {
	bool g() {
		Factory<Strategy, std::string, Strategy* (*)()>::getInstance()->addCreator("titfortatkind", createTitForTatKind);
		return true;//у каждого класса
	}

	bool b = g();
}

void TitForTatKind::getRes(bool s1, bool s2) {
	betrayed = s1 | s2;
	return;
}

bool TitForTatKind::makeMove() {
	return betrayed;
}

std::string TitForTatKind::getName() {
	return name;
}

void TitForTatKind::reload() {
	betrayed = false;
}

Strategy* createTitForTatKind() {
	return new TitForTatKind;
}
