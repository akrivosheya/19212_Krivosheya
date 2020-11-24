#include "Tournament.h"
#include "Factory.h"

namespace {
	bool g() {
		Factory<Game, std::string, Game* (*)()>::getInstance()->addCreator("tournament", createTournament);
		return true;//у каждого класса
	}

	bool b = g();
}

Tournament::Tournament() {
	pointS1 = pointS2 = pointS3 = 0;
	name = "Tournament";
}

void Tournament::Play(int& steps, std::vector<Strategy*>& strategys, const char* file) {
	std::ofstream matrix(file);
	matrix << "s1 s2 s3" << std::endl;
	bool moveS1, moveS2, moveS3;
	int getS1, getS2, getS3;
	pointS1 = pointS2 = pointS3 = 0;
	int limit = strategys.size();
	int battle = 1;
	std::vector<int> victories(limit);
	for (int i = 0; i < limit; ++i) {
		for (int j = i + 1; j < limit; ++j) {
			for (int k = j + 1; k < limit; ++k) {
				matrix << "s1 - " << strategys[i]->getName() << "; s2 - " << strategys[j]->getName() <<
					"; s3 - " << strategys[k]->getName() << std::endl;
				for (int s = 0; s < steps; ++s) {
					GetMoves(moveS1, moveS2, moveS3, strategys[i], strategys[j], strategys[k]);
					GetGets(moveS1, moveS2, moveS3, getS1, getS2, getS3);
					GetPoints(pointS1, pointS2, pointS3, getS1, getS2, getS3);
					PutRes(moveS1, moveS2, moveS3, strategys[i], strategys[j], strategys[k]);
					matrix << Moves(moveS1, moveS2, moveS3) << "  =>  " << pointS1 << " " << pointS2 << " " << pointS3 << std::endl;
				}
				matrix << std::endl;
				SetWinners(pointS1, pointS2, pointS3, victories[i], victories[j], victories[k]);
				std::cout << battle << ") ";
				++battle;
				PrintRes(pointS1, pointS2, pointS3, strategys[i], strategys[j], strategys[k]);
				Reload(strategys[i], strategys[j], strategys[k]);
				pointS1 = pointS2 = pointS3 = 0;
			}
		}
	}
	std::cout << std::endl << "Results:" << std::endl;
	for (int i = 0; i < limit; ++i) {
		std::cout << i << ") " << strategys[i]->getName() << " - " << victories[i] << std::endl;
	}
	matrix.close();
}

void Tournament::Reload(Strategy* S1, Strategy* S2, Strategy* S3) {
	S1->reload();
	S2->reload();
	S3->reload();
}

Game* createTournament() {
	return new Tournament();
}
