#include "pch.h"
#include <fstream>
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
#include "STFT.h"

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
	if (i > argc - 1) {
		if (!SetModeOptional(size, mode)) {
			return false;
		}
		steps = OPTIONALSTEPS;
	}
	else {
		if (IsMode(argv[i])) {
			mode = argv[i];
			++i;
			if (i > argc - 1) {
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
			if (i > argc - 1) {
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

int countTournament = 0;
std::string mode = "IsNotSet";
int pointS1 = 0, pointS2 = 0, pointS3 = 0, steps = 0;
std::vector<Strategy*> strategys;

int Game(int argc, char* argv[]) {
	if (argc < 4) return -1;

	std::ofstream matrix("Matrix.txt");
	matrix << "s1 s2 s3" << std::endl;

	int i = 1;
	for (; (i <= argc - 1) && !IsMode(argv[i]) && !IsDigit(argv[i]); ++i) {
		strategys.push_back(Factory<Strategy, std::string, Strategy* (*)()>::getInstance()->makeStrategy(argv[i]));
	}

	if (!SetOptions(strategys.size(), mode, steps, i, argc, argv)) {
		return -1;
	}

	bool moveS1, moveS2, moveS3;
	int getS1, getS2, getS3;

	if (mode == "fast") {
		for (int j = 0; j < steps; ++j) {
			matrix << "s1 - " << strategys[0]->getName() << "; s2 - " << strategys[1]->getName() <<
				"; s2 - " << strategys[2]->getName() << std::endl;
			GetMoves(moveS1, moveS2, moveS3, strategys[0], strategys[1], strategys[2]);
			GetGets(moveS1, moveS2, moveS3, getS1, getS2, getS3);
			GetPoints(pointS1, pointS2, pointS3, getS1, getS2, getS3);
			PutRes(moveS1, moveS2, moveS3, strategys[0], strategys[1], strategys[2]);
			matrix << Moves(moveS1, moveS2, moveS3) << "  =>  " << pointS1 << " " << pointS2 << " " << pointS3 << std::endl;
		}
		PrintRes(pointS1, pointS2, pointS3, strategys[0], strategys[1], strategys[2]);
	}
	else if (mode == "detailed") {
		matrix << "s1 - " << strategys[0]->getName() << "; s2 - " << strategys[1]->getName() <<
			"; s2 - " << strategys[2]->getName() << std::endl;
		std::string step;
		std::cin >> step;
		while (step != "quit") {
			GetMoves(moveS1, moveS2, moveS3, strategys[0], strategys[1], strategys[2]);
			GetGets(moveS1, moveS2, moveS3, getS1, getS2, getS3);
			GetPoints(pointS1, pointS2, pointS3, getS1, getS2, getS3);
			PutRes(moveS1, moveS2, moveS3, strategys[0], strategys[1], strategys[2]);
			matrix << Moves(moveS1, moveS2, moveS3) << "  =>  " << pointS1 << " " << pointS2 << " " << pointS3 << std::endl;
			std::cout << Moves(moveS1, moveS2, moveS3) << "  =>  " << getS1 << " " << getS2 << " " << getS3
				<< "  =>  " << pointS1 << " " << pointS2 << " " << pointS3 << std::endl;
			std::cin >> step;
		}
		PrintRes(pointS1, pointS2, pointS3, strategys[0], strategys[1], strategys[2]);
	}
	else {
		int limit = strategys.size();
		int battle = 1;
		std::vector<int> points(limit);
		for (int i = 0; i < limit; ++i) {
			for (int j = i + 1; j < limit; ++j) {
				for (int k = j + 1; k < limit; ++k) {
					matrix << "s1 - " << strategys[i]->getName() << "; s2 - " << strategys[j]->getName() <<
						"; s2 - " << strategys[k]->getName() << std::endl;
					for (int s = 0; s < steps; ++s) {
						GetMoves(moveS1, moveS2, moveS3, strategys[i], strategys[j], strategys[k]);
						GetGets(moveS1, moveS2, moveS3, getS1, getS2, getS3);
						GetPoints(pointS1, pointS2, pointS3, getS1, getS2, getS3);
						PutRes(moveS1, moveS2, moveS3, strategys[i], strategys[j], strategys[k]);
						matrix << Moves(moveS1, moveS2, moveS3) << "  =>  " << pointS1 << " " << pointS2 << " " << pointS3 << std::endl;
					}
					matrix << std::endl;
					SetWinners(pointS1, pointS2, pointS3, points[i], points[j], points[k]);
					std::cout << battle << ") ";
					++battle;
					++countTournament;
					PrintRes(pointS1, pointS2, pointS3, strategys[i], strategys[j], strategys[k]);
					Reload(strategys[i], strategys[j], strategys[k]);
					pointS1 = pointS2 = pointS3 = 0;
				}
			}
		}
		std::cout << std::endl << "Results:" << std::endl;
		for (int i = 0; i < limit; ++i) {
			std::cout << i << ") " << strategys[i]->getName() << " - " << points[i] << std::endl;
		}
	}

	matrix.close();
	return 0;

}

TEST(Options, Fast50) {
	char* argv[] = { "prog", "kind", "traitor", "backandforth", "fast", "50" };
	int res = Game(6, argv);
  EXPECT_EQ(res, 0);
  EXPECT_EQ(mode, "fast");
  EXPECT_EQ(steps, 50);
  EXPECT_EQ(strategys[0]->getName(), "Kind");
  EXPECT_EQ(strategys[1]->getName(), "Traitor");
  EXPECT_EQ(strategys[2]->getName(), "BackAndForth");
  mode = "IsNotSet";
  pointS1 = pointS2 = pointS3 = steps = 0;
  strategys.clear();
}

TEST(Options, Fast) {
	char* argv[] = { "prog", "kind", "traitor", "backandforth", "fast"};
	int res = Game(5, argv);
	EXPECT_EQ(res, 0);
	EXPECT_EQ(mode, "fast");
	EXPECT_EQ(steps, 100);
	EXPECT_EQ(strategys[0]->getName(), "Kind");
	EXPECT_EQ(strategys[1]->getName(), "Traitor");
	EXPECT_EQ(strategys[2]->getName(), "BackAndForth");
	mode = "IsNotSet";
	pointS1 = pointS2 = pointS3 = steps = 0;
	strategys.clear();
}

TEST(Options, Detailed150) {
	char* argv[] = { "prog", "southampton", "titfortatkind", "titfortatanger", "detailed", "150" };
	int res = Game(6, argv);
	EXPECT_EQ(res, 0);
	EXPECT_EQ(mode, "detailed");
	EXPECT_EQ(steps, 150);
	EXPECT_EQ(strategys[0]->getName(), "Southampton");
	EXPECT_EQ(strategys[1]->getName(), "TitForTatKind");
	EXPECT_EQ(strategys[2]->getName(), "TitForTatAnger");
	mode = "IsNotSet";
	pointS1 = pointS2 = pointS3 = steps = 0;
	strategys.clear();
}

TEST(Options, Tournament90) {
	char* argv[] = { "prog", "kind", "traitor", "backandforth", "southampton", "titfortatkind", "titfortatanger", "tournament", "90" };
	int res = Game(9, argv);
	EXPECT_EQ(res, 0);
	EXPECT_EQ(mode, "tournament");
	EXPECT_EQ(steps, 90);
	EXPECT_EQ(strategys[0]->getName(), "Kind");
	EXPECT_EQ(strategys[1]->getName(), "Traitor");
	EXPECT_EQ(strategys[2]->getName(), "BackAndForth");
	EXPECT_EQ(strategys[3]->getName(), "Southampton");
	EXPECT_EQ(strategys[4]->getName(), "TitForTatKind");
	EXPECT_EQ(strategys[5]->getName(), "TitForTatAnger");
	EXPECT_EQ(countTournament, 6 * 5 * 4 / 3 / 2);
	mode = "IsNotSet";
	pointS1 = pointS2 = pointS3 = steps = countTournament = 0;
	strategys.clear();
}

TEST(Options, OptionalDetailed) {
	char* argv[] = { "prog", "southampton", "southampton", "titfortatanger"};
	int res = Game(4, argv);
	EXPECT_EQ(res, 0);
	EXPECT_EQ(mode, "detailed");
	EXPECT_EQ(steps, 100);
	EXPECT_EQ(strategys[0]->getName(), "Southampton");
	EXPECT_EQ(strategys[1]->getName(), "Southampton");
	EXPECT_EQ(strategys[2]->getName(), "TitForTatAnger");
	mode = "IsNotSet";
	pointS1 = pointS2 = pointS3 = steps = countTournament = 0;
	strategys.clear();
}

TEST(Options, OptionalTournament60) {
	char* argv[] = { "prog", "southampton", "southampton", "titfortatanger", "traitor", "stft", "60" };
	int res = Game(7, argv);
	EXPECT_EQ(res, 0);
	EXPECT_EQ(mode, "tournament");
	EXPECT_EQ(steps, 60);
	EXPECT_EQ(strategys[0]->getName(), "Southampton");
	EXPECT_EQ(strategys[1]->getName(), "Southampton");
	EXPECT_EQ(strategys[2]->getName(), "TitForTatAnger");
	EXPECT_EQ(strategys[3]->getName(), "Traitor");
	EXPECT_EQ(strategys[4]->getName(), "STFT");
	EXPECT_EQ(countTournament, 5 * 4 / 2);
	mode = "IsNotSet";
	pointS1 = pointS2 = pointS3 = steps = countTournament = 0;
	strategys.clear();
}

TEST(Options, OptionalTournament) {
	char* argv[] = { "prog", "southampton", "southampton", "titfortatanger", "traitor", "stft", "kind"};
	int res = Game(7, argv);
	EXPECT_EQ(res, 0);
	EXPECT_EQ(mode, "tournament");
	EXPECT_EQ(steps, 100);
	EXPECT_EQ(strategys[0]->getName(), "Southampton");
	EXPECT_EQ(strategys[1]->getName(), "Southampton");
	EXPECT_EQ(strategys[2]->getName(), "TitForTatAnger");
	EXPECT_EQ(strategys[3]->getName(), "Traitor");
	EXPECT_EQ(strategys[4]->getName(), "STFT");
	EXPECT_EQ(strategys[5]->getName(), "Kind");
	EXPECT_EQ(countTournament, 6 * 5 * 4 / 3 / 2);
	mode = "IsNotSet";
	pointS1 = pointS2 = pointS3 = steps = countTournament = 0;
	strategys.clear();
}

TEST(Options, FewStrategys) {
	char* argv[] = { "prog", "southampton", "kind"};
	int res = Game(3, argv);
	EXPECT_EQ(res, -1);
	mode = "IsNotSet";
	pointS1 = pointS2 = pointS3 = steps = countTournament = 0;
	strategys.clear();
}

TEST(Options, NotRealStrategy) {
	char* argv[] = { "prog", "stft", "kind", "blablabla", "traitor" };
	int res;
	EXPECT_ANY_THROW(res = Game(5, argv));
	mode = "IsNotSet";
	pointS1 = pointS2 = pointS3 = steps = countTournament = 0;
	strategys.clear();
}
