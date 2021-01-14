#include "Game.h"

Game::Game():decisions(3),
			gets(3), 
			points(3),
			rules(8){}

void Game::SetRules(std::istream& is) {
	std::vector<char> symbs(3);
	int index = 0;
	for (int j = 0; j < rules.size(); ++j) {
		is >> symbs[0] >> symbs[1] >> symbs[2];
		for (auto iter = symbs.begin(); iter != symbs.end(); ++iter) {
			index = (index << 1) + ((*iter == 'C') ? 1 : 0);
		}
		is >> rules[index];
		index = 0;
	}
}

void Game::SetDecisions(Strategy* S1, Strategy* S2, Strategy* S3) {
	decisions[0] = S1->makeDecision();
	decisions[1] = S2->makeDecision();
	decisions[2] = S3->makeDecision();
}

void Game::SetGets() {
	int index = 0;
	index = index + decisions[0];
	index = (index << 1) + decisions[1];
	index = (index << 1) + decisions[2];
	int codeOfGets = rules[index];
	gets[0] = codeOfGets / 100;
	gets[1] = (codeOfGets / 10) % 10;
	gets[2] = codeOfGets % 10;
}

void Game::SetPoints() {
	points[0] += gets[0];
	points[1] += gets[1];
	points[2] += gets[2];
}

void Game::GiveDecisions(Strategy* S1, Strategy* S2, Strategy* S3) {
	S1->putDecisions(decisions[1], decisions[2]);
	S2->putDecisions(decisions[0], decisions[2]);
	S3->putDecisions(decisions[0], decisions[1]);
}

void Game::SetWinners(int& S1, int& S2, int& S3) {
	bool firstIsWinner = true, secondIsWinner = false, ThirdIsWinner = false;
	int max = points[0];
	if (max <= points[1]) {
		secondIsWinner = true;
		max = points[1];
		firstIsWinner = points[0] == max;
	}
	if (max <= points[2]) {
		ThirdIsWinner = true;
		max = points[2];
		firstIsWinner = points[0] == max;
		secondIsWinner = points[1] == max;
	}
	S1 += (firstIsWinner) ? 1 : 0;
	S2 += (secondIsWinner) ? 1 : 0;
	S3 += (ThirdIsWinner) ? 1 : 0;
}
