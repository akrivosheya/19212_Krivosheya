#include "Fast.h"
#include "Factory.h"

namespace {
	bool g() {
		Factory<Game, std::string, Game* (*)()>::getInstance()->addCreator("fast", createFast);
		return true;//у каждого класса
	}

	bool b = g();
}

Fast::Fast(){
	name = "Fast";
}

void Fast::Play(const char* file, Printer& print) {
	for (int j = 0; j < steps; ++j) {
		GetMoves(strategys[0], strategys[1], strategys[2]);
		GetGets(file);
		GetPoints();
		PutRes(strategys[0], strategys[1], strategys[2]);
	}
	print.PrintRes(strategys[0], strategys[1], strategys[2], pointS1, pointS2, pointS3);
}

Game* createFast() {
	return new Fast();
}
