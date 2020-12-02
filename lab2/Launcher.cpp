#include "pch.h"
#include "Launcher.h"
#include "Preparation.h"


Launcher::Launcher(): countTournament(0),
	pointS1(0),
	pointS2(0),
	pointS3(0),
	moveSouth1(true),
	moveSouth2(true),
	moveSTFT1(true),
	moveBack(true),
	moveKind(true),
	moveTraitor(true),
	moveTK(true),
	moveTA(true),
	nameOfGame("Nothing"){}

int Launcher::Launch(int argc, char* argv[], std::string& mode, int& steps, std::vector<Strategy*>& strategys) {
	if (argc < 4) return -1;
	steps = 0;
	mode = "IsNotSet";
	Preparation P;
	Game* G = P.Prepare(steps, mode, strategys, argc, argv);
	if (!G) {
		return -1;
	}
	G->Play(steps, strategys, "Matrix.txt");
	countTournament = G->countTournament;
	moveSouth1 = G->moveSouth1;
	moveSouth2 = G->moveSouth2;
	moveSTFT1 = G->moveSTFT1;
	moveBack = G->moveBack;
	moveKind = G->moveKind;
	moveTraitor = G->moveTraitor;
	moveTK = G->moveTK;
	moveTA = G->moveTA;
	nameOfGame = G->GetName();
	pointS1 = G->GetPoint(1);
	pointS2 = G->GetPoint(2);
	pointS3 = G->GetPoint(3);
	delete G;
	return 0;
}

int Launcher::GetCount() {
	return countTournament;
}

bool Launcher::GetSouth1() {
	return moveSouth1;
}

bool Launcher::GetSouth2() {
	return moveSouth2;
}

bool Launcher::GetSTFT1() {
	return moveSTFT1;
}

bool Launcher::GetBack() {
	return moveBack;
}

bool Launcher::GetKind() {
	return moveKind;
}

bool Launcher::GetTraitor() {
	return moveTraitor;
}

bool Launcher::GetTK() {
	return moveTK;
}

bool Launcher::GetTA() {
	return moveTA;
}

int Launcher::GetPoint(int i) {
	switch (i) {
	case 1:
		return pointS1;
	case 2:
		return pointS2;
	case 3:
		return pointS3;
	}
}
