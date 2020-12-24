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

void Detailed::Play(Printer& print) {
	std::string step;
	std::cin >> step;
	while (step != "quit") {
		SetDecisions(strategys[0], strategys[1], strategys[2]);
		SetGets();
		SetPoints();
		GiveDecisions(strategys[0], strategys[1], strategys[2]);
		print.PrintDetailedRes(decisions, gets, points);
		std::cin >> step;
	}
	print.PrintRes(strategys, points, 0, 1, 2);
}
