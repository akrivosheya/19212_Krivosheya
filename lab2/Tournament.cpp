#include "Tournament.h"
#include "Factory.h"

namespace {
	bool g() {
		Factory<Game, std::string, Game* (*)()>::getInstance()->addCreator("tournament", createTournament);
		return true;//у каждого класса
	}

	bool b = g();
}

Tournament::Tournament(){
	name = "Tournament";
}

void Tournament::Play(const char* file, Printer& print) {
	int limit = strategys.size();
	std::vector<int> victories(limit);
	for (int i = 0; i < limit; ++i) {
		for (int j = i + 1; j < limit; ++j) {
			for (int k = j + 1; k < limit; ++k) {
				for (int s = 0; s < steps; ++s) {
					SetDecisions(strategys[i], strategys[j], strategys[k]);
					SetGets(file);
					SetPoints();
					GiveDecisions(strategys[i], strategys[j], strategys[k]);
				}
				SetWinners(victories[i], victories[j], victories[k]);
				print.PrintRes(strategys[i], strategys[j], strategys[k], pointS1, pointS2, pointS3);
				Reload(strategys[i], strategys[j], strategys[k]);
				pointS1 = pointS2 = pointS3 = 0;
				++tournamentCount;//для тестов
			}
		}
	}
	print.PrintTournamentRes(strategys, victories);
}

void Tournament::Reload(Strategy* S1, Strategy* S2, Strategy* S3) {
	S1->reload();
	S2->reload();
	S3->reload();
}

Game* createTournament() {
	return new Tournament();
}
