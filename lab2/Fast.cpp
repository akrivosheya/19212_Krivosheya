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

void Fast::Play(Printer& print) {
	for (int j = 0; j < steps; ++j) {
		SetDecisions(strategys[0], strategys[1], strategys[2]);
		//для тестов
		if (j > 15) {
			traitor1ForTest &= !decisions[0];
			traitor2ForTest &= !decisions[1];
			titfortat1ForTest &= (j % 2) ? !decisions[0] : decisions[0];
			kind1ForTest &= decisions[0];
			kind2ForTest &= decisions[1];
			backandforth3ForTest &= (j % 2) ? decisions[2] : !decisions[2];
		}
		//------------
		SetGets();
		SetPoints();
		GiveDecisions(strategys[0], strategys[1], strategys[2]);
	}
	print.PrintRes(strategys, points, 0, 1, 2);
}
