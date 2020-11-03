#include "Kind.h"
#include "Factory.h"

namespace{
	bool g() {
		Factory<Strategy, std::string, Strategy* (*)()>::getInstance()->addCreator("kind", createKind);
		return true;//у каждого класса
	}

	bool b = g();
}

void Kind::getRes(bool s1, bool s2) {
	return;
}

bool Kind::makeMove() {
	return c;
}

std::string Kind::getName() {
	return name;
}

Strategy* createKind() {
	return new Kind;
}
