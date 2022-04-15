#include "Kind.h"
#include "Factory.h"

Strategy* createKind();

namespace{
	bool g() {
		Factory<Strategy, std::string, Strategy* (*)()>::getInstance()->addCreator("kind", createKind);
		return true;//у каждого класса
	}

	bool b = g();
}

Strategy* createKind() {
	return new Kind;
}
