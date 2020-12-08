#include "Game.h"
#include <fstream>

Game::Game(): steps(0),
			moveS1(false),
			moveS2(false), 
			moveS3(false), 
			getS1(0), 
			getS2(0), 
			getS3(0), 
			pointS1(0), 
			pointS2(0), 
			pointS3(0){}

std::string Game::Moves() {
	std::string m1 = ((moveS1) ? "C" : "D");
	std::string m2 = ((moveS2) ? "C" : "D");
	std::string m3 = ((moveS3) ? "C" : "D");
	std::string moves = " " + m1 + "  " + m2 + "  " + m3;
	return moves;
}

void Game::GetMoves(Strategy* S1, Strategy* S2, Strategy* S3) {
	moveS1 = S1->makeMove();
	moveS2 = S2->makeMove();
	moveS3 = S3->makeMove();
}

void Game::GetGets(const char* file) {
	bool found = false;
	char c1, c2, c3;
	std::ifstream matrix(file);
	while (!found) {
		matrix >> c1 >> c2 >> c3 >> getS1 >> getS2 >> getS3;
		if (((moveS1 && (c1 == 'c')) || (!moveS1 && (c1 == 'd')))
			&& ((moveS2 && (c2 == 'c')) || (!moveS2 && (c2 == 'd')))
			&& ((moveS3 && (c3 == 'c')) || (!moveS3 && (c3 == 'd')))) {
			found = true;
		}
	}
	matrix.close();
}

std::string Game::GetName() {
	return name;
}

void Game::GetPoints() {
	pointS1 += getS1;
	pointS2 += getS2;
	pointS3 += getS3;
}

void Game::PutRes(Strategy* S1, Strategy* S2, Strategy* S3) {
	S1->getRes(moveS2, moveS3);
	S2->getRes(moveS1, moveS3);
	S3->getRes(moveS1, moveS2);
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

int Game::GetPoint(int i) {
	switch (i) {
	case 1:
		return pointS1;
	case 2:
		return pointS2;
	case 3:
		return pointS3;
	}
}

void Game::SetSteps(int& steps) {
	this->steps = steps;
}

void Game::SetStrategys(std::vector<Strategy*>& strategys) {
	this->strategys = strategys;
}
