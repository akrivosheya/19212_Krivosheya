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
	pointS1 = pointS2 = pointS3 = 0;
	name = "Detailed";
}

void Detailed::Play(int& steps, std::vector<Strategy*>& strategys, const char* file) {
	std::ofstream matrix(file);
	matrix << "s1 s2 s3" << std::endl;
	bool moveS1, moveS2, moveS3;
	int getS1, getS2, getS3;
	pointS1 = pointS2 = pointS3 = 0;
	matrix << "s1 - " << strategys[0]->getName() << "; s2 - " << strategys[1]->getName() <<
		"; s3 - " << strategys[2]->getName() << std::endl;
	std::string step;
	std::cin >> step;
	while (step != "quit") {
		GetMoves(moveS1, moveS2, moveS3, strategys[0], strategys[1], strategys[2]);
		GetGets(moveS1, moveS2, moveS3, getS1, getS2, getS3);
		GetPoints(pointS1, pointS2, pointS3, getS1, getS2, getS3);
		PutRes(moveS1, moveS2, moveS3, strategys[0], strategys[1], strategys[2]);
		matrix << Moves(moveS1, moveS2, moveS3) << "  =>  " << pointS1 << " " << pointS2 << " " << pointS3 << std::endl;
		std::cout << Moves(moveS1, moveS2, moveS3) << "  =>  " << getS1 << " " << getS2 << " " << getS3
			<< "  =>  " << pointS1 << " " << pointS2 << " " << pointS3 << std::endl;
		std::cin >> step;
	}
	PrintRes(pointS1, pointS2, pointS3, strategys[0], strategys[1], strategys[2]);
	matrix.close();
}

Game* createDetailed() {
	return new Detailed();
}
