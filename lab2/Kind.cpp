#include "Kind.h"
#include "Factory.h"

namespace{
	bool g() {
		Factory<Strategy, std::string, Strategy* (*)()>::getInstance()->addCreator("kind", createKind);
		return true;//у каждого класса
	}

	bool b = g();
}

void Kind::putDecisions(bool decision1, bool decision2) {
	return;
}

bool Kind::makeDecision() {
	return help;
}

std::string Kind::getName() {
	return name;
}
