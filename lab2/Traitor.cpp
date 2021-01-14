#include "Traitor.h"
#include "Factory.h"

Strategy* createTraitor();

namespace {
	bool g() {
		Factory<Strategy, std::string, Strategy* (*)()>::getInstance()->addCreator("traitor", createTraitor);
		return true;//у каждого класса
	}

	bool b = g();
}

Strategy* createTraitor() {
	return new Traitor;
}
