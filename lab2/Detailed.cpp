#include "pch.h"
#include "Detailed.h"
#include "Factory.h"

namespace {
	bool g() {
		Factory<Game, std::string, Game* (*)()>::getInstance()->addCreator("detailed", createDetailed);
		return true;//у каждого класса
	}

	bool b = g();
}

Detailed::Detailed() {
	name = "Detailed";
}

void Detailed::Play(int& steps, std::vector<Strategy*>& strategys, const char* file) {
	std::ofstream matrix(file);
	matrix << "s1 s2 s3" << std::endl;
	matrix << "s1 - " << strategys[0]->getName() << "; s2 - " << strategys[1]->getName() <<
		"; s3 - " << strategys[2]->getName() << std::endl;
	std::string step;
	std::cin >> step;

	//int i = 0;  //for tests

	while (step != "quit") {
		GetMoves(strategys[0], strategys[1], strategys[2]);
		GetGets();
		GetPoints();
		PutRes(strategys[0], strategys[1], strategys[2]);
		matrix << Moves() << "  =>  " << pointS1 << " " << pointS2 << " " << pointS3 << std::endl;
		std::cout << Moves() << "  =>  " << getS1 << " " << getS2 << " " << getS3
			<< "  =>  " << pointS1 << " " << pointS2 << " " << pointS3 << std::endl;
		std::cin >> step;

		/*++i;
		if (i > 10) {
			step = "quit";
		}*/

	}
	PrintRes(strategys[0], strategys[1], strategys[2]);
	matrix.close();
}

Game* createDetailed() {
	return new Detailed();
}
