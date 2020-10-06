#include "Zergling.h"

void Zergling::move(int x, int y) {
	std::cout << "Zergling move" << std::endl;
}

Zergling* createZergling() {
	return new Zergling;
}
