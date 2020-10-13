#include "Kind.h"
#include "Factory.h"

namespace{
	bool g() {
		Factory::getInstance()->addCreator("kind", createKind);
		return true;//у каждого класса
	}
}

void Kind::getRes(int s1, int s2) {
	return;
}

bool Kind::makeMove() {
	return true;
}

Kind* createKind() {
	return new Kind;
}
