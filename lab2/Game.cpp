#include "Game.h"
#include <fstream>

Game::Game(): steps(0),
			decisionS1(false),
			decisionS2(false),
			decisionS3(false),
			getS1(0), 
			getS2(0), 
			getS3(0), 
			pointS1(0), 
			pointS2(0), 
			pointS3(0),
			tournamentCount(0),
			traitor1(true), 
			traitor2(true),
			kind1(true),
			kind2(true),
			backandforth3(true),
			titfortat1(true){}

Game::~Game() {
	strategys.clear();
}

std::string Game::Decisions() {
	std::string m1 = ((decisionS1) ? "C" : "D");
	std::string m2 = ((decisionS2) ? "C" : "D");
	std::string m3 = ((decisionS3) ? "C" : "D");
	std::string moves = " " + m1 + "  " + m2 + "  " + m3;
	return moves;
}

void Game::SetDecisions(Strategy* S1, Strategy* S2, Strategy* S3) {
	decisionS1 = S1->makeDecision();
	decisionS2 = S2->makeDecision();
	decisionS3 = S3->makeDecision();
}

void Game::SetGets(const char* file) {
	bool found = false;
	char c1, c2, c3;
	std::ifstream matrix(file);
	while (!found) {
		matrix >> c1 >> c2 >> c3 >> getS1 >> getS2 >> getS3;
		if (((decisionS1 && (c1 == 'c')) || (!decisionS1 && (c1 == 'd')))
			&& ((decisionS2 && (c2 == 'c')) || (!decisionS2 && (c2 == 'd')))
			&& ((decisionS3 && (c3 == 'c')) || (!decisionS3 && (c3 == 'd')))) {
			found = true;
		}
	}
	matrix.close();
}

void Game::SetPoints() {
	pointS1 += getS1;
	pointS2 += getS2;
	pointS3 += getS3;
}

void Game::GiveDecisions(Strategy* S1, Strategy* S2, Strategy* S3) {
	S1->putDecisions(decisionS2, decisionS3);
	S2->putDecisions(decisionS1, decisionS3);
	S3->putDecisions(decisionS1, decisionS2);
}

void Game::SetWinners(int& S1, int& S2, int& S3) {
	bool max1 = true, max2 = false, max3 = false;
	int max = pointS1;
	if (max <= pointS2) {
		max2 = true;
		if (max != pointS2) {
			max1 = false;
			max = pointS2;
		}
	}
	if (max <= pointS3) {
		max3 = true;
		if (max != pointS3) {
			max = pointS3;
			max1 = (pointS1 == max) ? true : false;
			max2 = (pointS2 == max) ? true : false;
		}
	}
	S1 += (max1) ? 1 : 0;
	S2 += (max2) ? 1 : 0;
	S3 += (max3) ? 1 : 0;
}

void Game::SetSteps(int& steps) {
	this->steps = steps;
}

void Game::SetStrategys(std::vector<Strategy*>& strategys) {
	this->strategys = strategys;
}
