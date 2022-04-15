#include "BattleCruiser.h"

void BattleCruiser::move(int x, int y) {
	std::cout << "BattleCruiser move" << std::endl;
}

BattleCruiser* createBattleCruiser() {
	return new BattleCruiser;
}
