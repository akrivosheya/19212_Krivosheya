#include "SiegeTank.h"

void SiegeTank::move(int x, int y) {
	std::cout << "SiegeTank move" << std::endl;
}

SiegeTank* createSiegeTank() {
	return new SiegeTank;
}
