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

void Tournament::Play(Printer& print) {
	int limit = strategys.size();
	std::vector<int> victories(limit);
	for (int i = 0; i < limit; ++i) {
		for (int j = i + 1; j < limit; ++j) {
			for (int k = j + 1; k < limit; ++k) {
				for (int s = 0; s < steps; ++s) {
					SetDecisions(strategys[i], strategys[j], strategys[k]);
					SetGets();
					SetPoints();
					GiveDecisions(strategys[i], strategys[j], strategys[k]);
				}
				SetWinners(victories[i], victories[j], victories[k]);
				print.PrintRes(strategys, points, i, j, k);
				Reload(strategys[i], strategys[j], strategys[k]);
				points.assign(3, 0);
				++tournamentCountForTest;
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
