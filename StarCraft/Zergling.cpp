#include "Zergling.h"

namespace{
	bool g(){
		Factory<Unit, std::string, Unit* (*)()>::getInstance->addCreator("zergling", createZergling);
		return true;//у каждого класса
	}
}

void Zergling::move(int x, int y) {
	std::cout << "Zergling move" << std::endl;
}

Zergling* createZergling() {
	return new Zergling;
}
