#include <memory>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
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

int main(int argc, char* argv[]) {
	if (argc < 4) return -1;

	/*FILE* matrix;
	fopen_s(&matrix, "Matrix.txt", "w");
	fprintf(matrix, "s1 s2 s3      s1 s2 s3\n");*/
	std::ofstream matrix("Matrix.txt");
	matrix << "s1 s2 s3      s1 s2 s3\n";

	int i = 1, steps = 0;
	std::string mode = "IsNotSet";
	std::unordered_map<int, Strategy*>  strategys;
	for (; (i <= argc) && !IsMode(argv[i]) && !IsDigit(argv[i]); ++i) {
		strategys.insert({ i, Factory<Strategy, std::string, Strategy* (*)()>::getInstance()->makeStrategy(argv[i]) });
	}

	if (!SetOptions(strategys.size(), mode, steps, i, argc, argv)) {
		return -1;
	}

	if (mode == "fast") {
		bool moveS1, moveS2, moveS3;
		int pointS1 = 0, pointS2 = 0, pointS3 = 0, getS1, getS2, getS3;
		for (int j = 0; j < steps; ++j) {
			moveS1 = (strategys.find(1)->second)->makeMove();//Подправить?????????????????
			moveS2 = (strategys.find(2)->second)->makeMove();
			moveS3 = (strategys.find(3)->second)->makeMove();
			getS1 = (moveS1) ? ((moveS2 && moveS3) ? 7 : ((moveS2 || moveS3) ? 3 : 0)) : ((moveS2 && moveS3) ? 9 : ((moveS2 || moveS3) ? 5 : 1));
			getS2 = (moveS2) ? ((moveS1 && moveS3) ? 7 : ((moveS1 || moveS3) ? 3 : 0)) : ((moveS1 && moveS3) ? 9 : ((moveS1 || moveS3) ? 5 : 1));
			getS3 = (moveS3) ? ((moveS2 && moveS1) ? 7 : ((moveS2 || moveS1) ? 3 : 0)) : ((moveS2 && moveS1) ? 9 : ((moveS2 || moveS1) ? 5 : 1));
			pointS1 += getS1;
			pointS2 += getS2;
			pointS3 += getS3;
			(strategys.find(1)->second)->getRes(moveS2, moveS3);
			(strategys.find(2)->second)->getRes(moveS1, moveS3);
			(strategys.find(3)->second)->getRes(moveS1, moveS2);
			/*fprintf(matrix, " %c  %c  %c  =>  %d  %d  %d\n", (moveS1) ? 'C' : 'D', (moveS1) ? 'C' : 'D', (moveS1) ? 'C' : 'D',
				pointS1, pointS2, pointS3);*/
			matrix << Moves(moveS1, moveS2, moveS3) << "  =>  " << pointS1 << " " << pointS2 << " " << pointS3 << std::endl;
		}
		std::cout << "s1 - " << pointS1 << "; s2 - " << pointS2 << "; s3 - " << pointS3 << std::endl;
	}
	else if (mode == "detailed") {
		bool moveS1, moveS2, moveS3;
		int pointS1 = 0, pointS2 = 0, pointS3 = 0 , getS1 = 0, getS2 = 0, getS3 = 0;
		std::string step;
		std::cin >> step;
		while (step != "quit") {
			std::cout << "ok" << std::endl;
			moveS1 = (strategys.find(1)->second)->makeMove();//Подправить, уменьшить?????????????????
			moveS2 = (strategys.find(2)->second)->makeMove();
			moveS3 = (strategys.find(3)->second)->makeMove();
			getS1 = (moveS1) ? ((moveS2 && moveS3) ? 7 : ((moveS2 || moveS3) ? 3 : 0)) : ((moveS2 && moveS3) ? 9 : ((moveS2 || moveS3) ? 5 : 1));
			getS2 = (moveS2) ? ((moveS1 && moveS3) ? 7 : ((moveS1 || moveS3) ? 3 : 0)) : ((moveS1 && moveS3) ? 9 : ((moveS1 || moveS3) ? 5 : 1));
			getS3 = (moveS3) ? ((moveS2 && moveS1) ? 7 : ((moveS2 || moveS1) ? 3 : 0)) : ((moveS2 && moveS1) ? 9 : ((moveS2 || moveS1) ? 5 : 1));
			pointS1 += getS1;
			pointS2 += getS2;
			pointS3 += getS3;
			(strategys.find(1)->second)->getRes(moveS2, moveS3);
			(strategys.find(2)->second)->getRes(moveS1, moveS3);
			(strategys.find(3)->second)->getRes(moveS1, moveS2);
			/*fprintf(matrix, " %c  %c  %c  =>  %d  %d  %d\n", (moveS1) ? 'C' : 'D', (moveS1) ? 'C' : 'D', (moveS1) ? 'C' : 'D',
				pointS1, pointS2, pointS3);*/
			matrix << Moves(moveS1, moveS2, moveS3) << "  =>  " << pointS1 << " " << pointS2 << " " << pointS3 << std::endl;
			std::cout << Moves(moveS1, moveS2, moveS3) << "  =>  " << getS1 << " " << getS2 << " " << getS3 << "  =>  " << pointS1 << " " << pointS2 << " " << pointS3 <<  std::endl;
			std::cin >> step;
		}
		std::cout << "s1 - " << pointS1 << "; s2 - " << pointS2 << "; s3 - " << pointS3 << std::endl;
		//std::cin >> i;
	}

	matrix.close();

	//std::unique_ptr<Strategy> u(Factory<Strategy, std::string, Strategy* (*)()>::getInstance()->makeStrategy(argv[1]));//смарт поинтер*/
}
