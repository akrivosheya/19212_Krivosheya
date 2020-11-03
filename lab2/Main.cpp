#include <memory>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include <vector>
#include "Strategy.h"
#include "Factory.h"
#include "BackAndForth.h"
#include "Kind.h"
#include "Traitor.h"
#include "Southampton.h"
#include "TitForTatAnger.h"
#include "TitForTatKind.h"

#define OPTIONALSTEPS 100

bool IsDigit(std::string str) {
	for (int i = 0; i < str.size(); ++i) {
		if (!isdigit(str[i])) {
			return false;
		}
	}
	return true;
}

bool IsMode(char* str) {
	return !(strcmp(str, "detailed") && strcmp(str, "fast") && strcmp(str, "tournament"));
}

bool SetModeOptional(const int& size, std::string& mode) {
	if (size < 3) {
		return false;
	}
	if (size == 3) {
		mode = "detailed";
	}
	else {
		mode = "tournament";
	}
	return true;
}

bool SetOptions(const int& size, std::string& mode, int& steps, int& i, const int& argc, char* argv[]) {
	if (i > argc) {
		if (!SetModeOptional(size, mode)) {
			return false;
		}
		steps = OPTIONALSTEPS;
	}
	else {
		if (IsMode(argv[i])) {
			mode = argv[i];
			++i;
			if (i > argc) {
				steps = OPTIONALSTEPS;
			}
			else {
				steps = atoi(argv[i]);
			}
		}
		else {
			if (!SetModeOptional(size, mode)) {
				return false;
			}
			++i;
			if (i > argc) {
				steps = OPTIONALSTEPS;
			}
			else {
				steps = atoi(argv[i]);
			}
		}
	}
	return true;
}

std::string Moves(bool& moveS1, bool& moveS2, bool& moveS3) {
	std::string m1 = ((moveS1) ? "C" : "D");
	std::string m2 = ((moveS2) ? "C" : "D");
	std::string m3 = ((moveS3) ? "C" : "D");
	std::string moves = " " + m1 + "  " + m2 + "  " + m3;
	return moves;
}

void GetMoves(bool& moveS1, bool& moveS2, bool& moveS3, Strategy* S1, Strategy* S2, Strategy* S3) {
	moveS1 = S1->makeMove();
	moveS2 = S2->makeMove();
	moveS3 = S3->makeMove();
}

void GetGets(bool& moveS1, bool& moveS2, bool& moveS3, int& getS1, int& getS2, int& getS3) {
	getS1 = (moveS1) ? ((moveS2 && moveS3) ? 7 : ((moveS2 || moveS3) ? 3 : 0)) : ((moveS2 && moveS3) ? 9 : ((moveS2 || moveS3) ? 5 : 1));
	getS2 = (moveS2) ? ((moveS1 && moveS3) ? 7 : ((moveS1 || moveS3) ? 3 : 0)) : ((moveS1 && moveS3) ? 9 : ((moveS1 || moveS3) ? 5 : 1));
	getS3 = (moveS3) ? ((moveS2 && moveS1) ? 7 : ((moveS2 || moveS1) ? 3 : 0)) : ((moveS2 && moveS1) ? 9 : ((moveS2 || moveS1) ? 5 : 1));
}

void GetPoints(int& pointS1, int& pointS2, int& pointS3, int& getS1, int& getS2, int& getS3) {
	pointS1 += getS1;
	pointS2 += getS2;
	pointS3 += getS3;
}

void PutRes(bool& moveS1, bool& moveS2, bool& moveS3, Strategy* S1, Strategy* S2, Strategy* S3) {
	S1->getRes(moveS2, moveS3);
	S2->getRes(moveS1, moveS3);
	S3->getRes(moveS1, moveS2);
}

void PrintRes(int& pointS1, int& pointS2, int& pointS3, Strategy* S1, Strategy* S2, Strategy* S3) {
	std::cout << S1->getName() << " - " << pointS1 << "; " << S2->getName() << " - " << pointS2 << 
		"; " << S3->getName() << " - " << pointS3 << std::endl;
}

void Reload(Strategy* S1, Strategy* S2, Strategy* S3) {
	S1->reload();
	S2->reload();
	S3->reload();
}

void SetWinners(int& pointS1, int& pointS2, int& pointS3, int& S1, int& S2, int& S3) {
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

int main(int argc, char* argv[]) {
	if (argc < 4) return -1;

	std::fstream matrix("Matrix.txt");
	matrix << "s1 s2 s3" << std::endl;

	int i = 1, steps = 0;
	std::string mode = "IsNotSet";
	std::unordered_map<int, Strategy*>  strategys;
	for (; (i <= argc) && !IsMode(argv[i]) && !IsDigit(argv[i]); ++i) {
		strategys.insert({ i, Factory<Strategy, std::string, Strategy* (*)()>::getInstance()->makeStrategy(argv[i]) });
	}

	if (!SetOptions(strategys.size(), mode, steps, i, argc, argv)) {
		return -1;
	}

	bool moveS1, moveS2, moveS3;
	int pointS1 = 0, pointS2 = 0, pointS3 = 0, getS1, getS2, getS3;

	if (mode == "fast") {
		for (int j = 0; j < steps; ++j) {
			GetMoves(moveS1, moveS2, moveS3, strategys.find(1)->second, strategys.find(2)->second, strategys.find(3)->second);
			GetGets(moveS1, moveS2, moveS3, getS1, getS2, getS3);
			GetPoints(pointS1, pointS2, pointS3, getS1, getS2, getS3);
			PutRes(moveS1, moveS2, moveS3, strategys.find(1)->second, strategys.find(2)->second, strategys.find(3)->second);
			matrix << Moves(moveS1, moveS2, moveS3) << "  =>  " << pointS1 << " " << pointS2 << " " << pointS3 << std::endl;
		}
		PrintRes(pointS1, pointS2, pointS3, strategys.find(1)->second, strategys.find(2)->second, strategys.find(3)->second);
	}
	else if (mode == "detailed") {
		matrix << "s1 - " << strategys.find(1)->second->getName() << "; s2 - " << strategys.find(2)->second->getName() <<
			"; s2 - " << strategys.find(3)->second->getName() << std::endl;
		std::string step;
		std::cin >> step;
		while (step != "quit") {
			GetMoves(moveS1, moveS2, moveS3, strategys.find(1)->second, strategys.find(2)->second, strategys.find(3)->second);
			GetGets(moveS1, moveS2, moveS3, getS1, getS2, getS3);
			GetPoints(pointS1, pointS2, pointS3, getS1, getS2, getS3);
			PutRes(moveS1, moveS2, moveS3, strategys.find(1)->second, strategys.find(2)->second, strategys.find(3)->second);
			matrix << Moves(moveS1, moveS2, moveS3) << "  =>  " << pointS1 << " " << pointS2 << " " << pointS3 << std::endl;
			std::cout << Moves(moveS1, moveS2, moveS3) << "  =>  " << getS1 << " " << getS2 << " " << getS3 
				<< "  =>  " << pointS1 << " " << pointS2 << " " << pointS3 <<  std::endl;
			std::cin >> step;
		}
		PrintRes(pointS1, pointS2, pointS3, strategys.find(1)->second, strategys.find(2)->second, strategys.find(3)->second);
	}
	else {
		int limit = strategys.size();
		int battle = 1;
		std::vector<int> players(limit);
		for (int i = 1; i <= limit; ++i) {
			for (int j = i + 1; j <= limit; ++j) {
				for (int k = j + 1; k <= limit; ++k) {
					for (int s = 0; s < steps; ++j) {
						GetMoves(moveS1, moveS2, moveS3, strategys.find(i)->second, strategys.find(j)->second, strategys.find(k)->second);
						GetGets(moveS1, moveS2, moveS3, getS1, getS2, getS3);
						GetPoints(pointS1, pointS2, pointS3, getS1, getS2, getS3);
						PutRes(moveS1, moveS2, moveS3, strategys.find(i)->second, strategys.find(j)->second, strategys.find(k)->second);
						matrix << Moves(moveS1, moveS2, moveS3) << "  =>  " << pointS1 << " " << pointS2 << " " << pointS3 << std::endl;
					}
					SetWinners(pointS1, pointS2, pointS3, players[i], players[j], players[k]);
					std::cout << battle << ") ";
					++battle;
					PrintRes(pointS1, pointS2, pointS3, strategys.find(i)->second, strategys.find(j)->second, strategys.find(k)->second);
					Reload(strategys.find(i)->second, strategys.find(j)->second, strategys.find(k)->second);
					pointS1 = pointS2 = pointS3 = 0;
				}
			}
		}
	}

	matrix.close();

	//std::unique_ptr<Strategy> u(Factory<Strategy, std::string, Strategy* (*)()>::getInstance()->makeStrategy(argv[1]));//смарт поинтер*/
}
