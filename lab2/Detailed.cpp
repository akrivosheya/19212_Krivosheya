#include "Detailed.h"
#include "Factory.h"

Game* createDetailed();

namespace {
	bool g() {
		Factory<Game, std::string, Game* (*)()>::getInstance()->addCreator("detailed", createDetailed);
		return true;//у каждого класса
	}

	bool b = g();
}

void Detailed::Play(Printer& print) {
	std::string step;
	print.ReadStep(step);
	while (step != "quit") {
		SetDecisions(strategys[0].get(), strategys[1].get(), strategys[2].get());
		SetGets();
		SetPoints();
		GiveDecisions(strategys[0].get(), strategys[1].get(), strategys[2].get());
		print.PrintDetailedRes(decisions, gets, points);
		print.ReadStep(step);
		step = "quit";
	}
	print.PrintRes(strategys, points, 0, 1, 2);
}

Game* createDetailed() {
	return new Detailed();
}
