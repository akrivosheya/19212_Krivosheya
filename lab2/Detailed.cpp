#include "Detailed.h"
#include "Factory.h"

namespace {
	bool g() {
		Factory<Game, std::string, Game* (*)()>::getInstance()->addCreator("detailed", createDetailed);
		return true;//у каждого класса
	}

	bool b = g();
}

Detailed::Detailed(){
	name = "Detailed";
}

void Detailed::Play(const char* file, Printer& print) {
	std::string step;
	std::cin >> step;
	while (step != "quit") {
		GetMoves(strategys[0], strategys[1], strategys[2]);
		GetGets(file);
		GetPoints();
		PutRes(strategys[0], strategys[1], strategys[2]);
		print.PrintDetailedRes(moveS1, moveS2, moveS3,
			pointS1, pointS2, pointS3,
			getS1, getS2, getS3);
		std::cin >> step;
	}
	print.PrintRes(strategys[0], strategys[1], strategys[2], pointS1, pointS2, pointS3);
}

Game* createDetailed() {
	return new Detailed();
}
