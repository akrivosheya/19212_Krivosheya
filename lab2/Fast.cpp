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
		SetDecisions(strategys[0], strategys[1], strategys[2]);
		//для тестов
		if (j > 15) {
			traitor1 &= !decisionS1;
			traitor2 &= !decisionS2;
			titfortat1 &= (j % 2) ? decisionS1 : !decisionS1;
			kind1 &= decisionS1;
			kind2 &= decisionS2;
			backandforth3 &= (j % 2) ? !decisionS3 : decisionS3;
		}
		//------------
		SetGets(file);
		SetPoints();
		GiveDecisions(strategys[0], strategys[1], strategys[2]);
	}
	print.PrintRes(strategys[0], strategys[1], strategys[2], pointS1, pointS2, pointS3);
}

Game* createFast() {
	return new Fast();
}
