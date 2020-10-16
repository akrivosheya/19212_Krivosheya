#include "Kind.h"
#include "Factory.h"

namespace{
	bool g() {
		Factory<Strategy, std::string, Strategy* (*)()>::getInstance()->addCreator("kind", createKind);
		return true;//у каждого класса
	}
}

void Kind::getRes(bool s1, bool s2) {
	return;
}

bool Kind::makeMove() {
	return c;
}

Strategy* createKind() {
	return new Kind;
}
