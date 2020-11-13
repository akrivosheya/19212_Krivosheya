#include "pch.h"
#include <fstream>
#include <vector>
#include "Factory.h"
#include "Game.h"

int countTournament = 0;
std::string mode = "IsNotSet";
int pointS1 = 0, pointS2 = 0, pointS3 = 0, steps = 0;
std::vector<Strategy*> strategys;
bool moveSouth1, moveSouth2, moveSTFT1, moveBack, moveKind, moveTraitor, moveTK, moveTA;

int Game(int argc, char* argv[]) {
	if (argc < 4) return -1;

	std::ofstream matrix("Matrix.txt");
	matrix << "s1 s2 s3" << std::endl;

	int i = 1;
	for (; (i <= argc - 1) && !IsMode(argv[i]) && !IsDigit(argv[i]); ++i) {
		strategys.push_back(Factory<Strategy, std::string, Strategy* (*)()>::getInstance()->makeStrategy(argv[i]));
		if (!strategys[i - 1]) {
			return -1;
		}
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
			if (i >= 10) {
				moveSouth1 &= !moveS1;
				moveSTFT1 &= !moveS3;
				moveSouth2 &= moveS2;
				moveBack = moveBack & ((j % 2) ? !moveS3 : moveS3);
				moveKind &= moveS1;
				moveTraitor &= !moveS2;
				moveTK &= moveS2 || moveS3;
				moveTA &= moveS2 && moveS3;
			}
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
		std::string step = "nothing";
		//std::cin >> step;
		while (step != "quit") {
			GetMoves(moveS1, moveS2, moveS3, strategys[0], strategys[1], strategys[2]);
			GetGets(moveS1, moveS2, moveS3, getS1, getS2, getS3);
			GetPoints(pointS1, pointS2, pointS3, getS1, getS2, getS3);
			PutRes(moveS1, moveS2, moveS3, strategys[0], strategys[1], strategys[2]);
			matrix << Moves(moveS1, moveS2, moveS3) << "  =>  " << pointS1 << " " << pointS2 << " " << pointS3 << std::endl;
			std::cout << Moves(moveS1, moveS2, moveS3) << "  =>  " << getS1 << " " << getS2 << " " << getS3
				<< "  =>  " << pointS1 << " " << pointS2 << " " << pointS3 << std::endl;
			//std::cin >> step;
			step = "quit";
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



TEST(Options, STFTfast) {
	mode = "IsNotSet";
	pointS1 = pointS2 = pointS3 = steps = 0;
	strategys.clear();
	char* argv[] = { "prog", "stft", "traitor", "backandforth", "fast", "50" };
	int res = Game(6, argv);
	EXPECT_EQ(res, 0);
	EXPECT_EQ(mode, "fast");
	EXPECT_EQ(steps, 50);
	EXPECT_EQ(strategys[0]->getName(), "STFT");
	EXPECT_EQ(strategys[1]->getName(), "Traitor");
	EXPECT_EQ(strategys[2]->getName(), "BackAndForth");
}
TEST(Options, Fast50) {
	mode = "IsNotSet";
	pointS1 = pointS2 = pointS3 = steps = 0;
	strategys.clear();
	char* argv[] = { "prog", "kind", "traitor", "backandforth", "fast", "50" };
	int res = Game(6, argv);
	EXPECT_EQ(res, 0);
	EXPECT_EQ(mode, "fast");
	EXPECT_EQ(steps, 50);
	EXPECT_EQ(strategys[0]->getName(), "Kind");
	EXPECT_EQ(strategys[1]->getName(), "Traitor");
	EXPECT_EQ(strategys[2]->getName(), "BackAndForth");
}

TEST(Options, Fast) {
	mode = "IsNotSet";
	pointS1 = pointS2 = pointS3 = steps = 0;
	strategys.clear();
	char* argv[] = { "prog", "kind", "traitor", "backandforth", "fast" };
	int res = Game(5, argv);
	EXPECT_EQ(res, 0);
	EXPECT_EQ(mode, "fast");
	EXPECT_EQ(steps, 100);
	EXPECT_EQ(strategys[0]->getName(), "Kind");
	EXPECT_EQ(strategys[1]->getName(), "Traitor");
	EXPECT_EQ(strategys[2]->getName(), "BackAndForth");
}

TEST(Options, Detailed150) {
	mode = "IsNotSet";
	pointS1 = pointS2 = pointS3 = steps = 0;
	strategys.clear();
	char* argv[] = { "prog", "southampton", "titfortatkind", "titfortatanger", "detailed", "150" };
	int res = Game(6, argv);
	EXPECT_EQ(res, 0);
	EXPECT_EQ(mode, "detailed");
	EXPECT_EQ(steps, 150);
	EXPECT_EQ(strategys[0]->getName(), "Southampton");
	EXPECT_EQ(strategys[1]->getName(), "TitForTatKind");
	EXPECT_EQ(strategys[2]->getName(), "TitForTatAnger");
}

TEST(Options, Tournament90) {
	mode = "IsNotSet";
	pointS1 = pointS2 = pointS3 = steps = countTournament = 0;
	strategys.clear();
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
}

TEST(Options, OptionalDetailed) {
	mode = "IsNotSet";
	pointS1 = pointS2 = pointS3 = steps = countTournament = 0;
	strategys.clear();
	char* argv[] = { "prog", "southampton", "southampton", "titfortatanger" };
	int res = Game(4, argv);
	EXPECT_EQ(res, 0);
	EXPECT_EQ(mode, "detailed");
	EXPECT_EQ(steps, 100);
	EXPECT_EQ(strategys[0]->getName(), "Southampton");
	EXPECT_EQ(strategys[1]->getName(), "Southampton");
	EXPECT_EQ(strategys[2]->getName(), "TitForTatAnger");
}

TEST(Options, OptionalTournament60) {
	mode = "IsNotSet";
	pointS1 = pointS2 = pointS3 = steps = countTournament = 0;
	strategys.clear();
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
}

TEST(Options, OptionalTournament) {
	mode = "IsNotSet";
	pointS1 = pointS2 = pointS3 = steps = countTournament = 0;
	strategys.clear();
	char* argv[] = { "prog", "southampton", "southampton", "titfortatanger", "traitor", "stft", "kind" };
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
}

TEST(Options, FewArgc) {
	mode = "IsNotSet";
	pointS1 = pointS2 = pointS3 = steps = countTournament = 0;
	strategys.clear();
	char* argv[] = { "prog", "southampton", "kind" };
	int res = Game(3, argv);
	EXPECT_EQ(res, -1);
}

TEST(Options, FewStrategys1) {
	mode = "IsNotSet";
	pointS1 = pointS2 = pointS3 = steps = countTournament = 0;
	strategys.clear();
	char* argv[] = { "prog", "southampton", "kind", "detailed"};
	int res = Game(4, argv);
	EXPECT_EQ(res, -1);
}

TEST(Options, NotRealStrategy) {
	mode = "IsNotSet";
	pointS1 = pointS2 = pointS3 = steps = countTournament = 0;
	strategys.clear();
	char* argv[] = { "prog", "stft", "kind", "blablabla", "traitor" };
	int res = Game(5, argv);;
	EXPECT_EQ(res, -1);
}

TEST(Strategys, Southampton) {
	mode = "IsNotSet";
	pointS1 = pointS2 = pointS3 = steps = countTournament = 0;
	strategys.clear();
	moveSouth1 = moveSouth2 = true;
	char* argv[] = { "prog", "southampton", "southampton", "traitor", "fast" };
	int res = Game(5, argv);
	EXPECT_EQ(strategys[0]->getName(), "Southampton");
	EXPECT_EQ(strategys[1]->getName(), "Southampton");
	EXPECT_TRUE(moveSouth1);
	EXPECT_TRUE(moveSouth2);
}

TEST(Strategys, STFT) {
	mode = "IsNotSet";
	pointS1 = pointS2 = pointS3 = steps = countTournament = 0;
	strategys.clear();
	moveSTFT1 = moveSouth2 = true;
	char* argv[] = { "prog", "stft", "stft", "backandforth", "fast" };
	int res = Game(5, argv);
	EXPECT_EQ(strategys[0]->getName(), "STFT");
	EXPECT_EQ(strategys[1]->getName(), "STFT");
	EXPECT_EQ(strategys[2]->getName(), "BackAndForth");
	EXPECT_TRUE(moveSTFT1);
	EXPECT_TRUE(moveSouth2);
}

TEST(Strategys, STFTSouthampton) {
	mode = "IsNotSet";
	pointS1 = pointS2 = pointS3 = steps = countTournament = 0;
	strategys.clear();
	moveSTFT1 = true;
	char* argv[] = { "prog", "stft", "southampton", "backandforth", "fast" };
	int res = Game(5, argv);
	EXPECT_EQ(strategys[0]->getName(), "STFT");
	EXPECT_EQ(strategys[1]->getName(), "Southampton");
	EXPECT_EQ(strategys[2]->getName(), "BackAndForth");
	EXPECT_TRUE(moveSTFT1);
	EXPECT_TRUE(moveSouth2);
}

TEST(Strategys, SouthamptonSTFT) {
	mode = "IsNotSet";
	pointS1 = pointS2 = pointS3 = steps = countTournament = 0;
	strategys.clear();
	moveSTFT1 = true;
	char* argv[] = { "prog", "southampton", "stft", "backandforth", "fast" };
	int res = Game(5, argv);
	EXPECT_EQ(strategys[0]->getName(), "Southampton");
	EXPECT_EQ(strategys[1]->getName(), "STFT");
	EXPECT_EQ(strategys[2]->getName(), "BackAndForth");
	EXPECT_TRUE(moveSouth1);
	EXPECT_TRUE(moveSouth2);
}

TEST(Strategys, KindTraitorBackAndForth) {
	mode = "IsNotSet";
	pointS1 = pointS2 = pointS3 = steps = countTournament = 0;
	strategys.clear();
	moveKind = moveTraitor = moveBack = true;
	char* argv[] = { "prog", "kind", "traitor", "backandforth", "fast" };
	int res = Game(5, argv);
	EXPECT_EQ(strategys[0]->getName(), "Kind");
	EXPECT_EQ(strategys[1]->getName(), "Traitor");
	EXPECT_EQ(strategys[2]->getName(), "BackAndForth");
	EXPECT_TRUE(moveKind);
	EXPECT_TRUE(moveTraitor);
	EXPECT_TRUE(moveBack);
}

TEST(Strategys, TitForTatKind1) {
	mode = "IsNotSet";
	pointS1 = pointS2 = pointS3 = steps = countTournament = 0;
	strategys.clear();
	moveTK = true;
	char* argv[] = { "prog", "titfortatkind", "kind", "backandforth", "fast" };
	int res = Game(5, argv);
	EXPECT_EQ(strategys[0]->getName(), "TitForTatKind");
	EXPECT_EQ(strategys[1]->getName(), "Kind");
	EXPECT_EQ(strategys[2]->getName(), "BackAndForth");
	EXPECT_TRUE(moveTK);
}

TEST(Strategys, TitForTatKind2) {
	mode = "IsNotSet";
	pointS1 = pointS2 = pointS3 = steps = countTournament = 0;
	strategys.clear();
	moveTK = true;
	char* argv[] = { "prog", "titfortatkind", "traitor", "backandforth", "fast" };
	int res = Game(5, argv);
	EXPECT_EQ(strategys[0]->getName(), "TitForTatKind");
	EXPECT_EQ(strategys[1]->getName(), "Traitor");
	EXPECT_EQ(strategys[2]->getName(), "BackAndForth");
	EXPECT_TRUE(moveTK);
}

TEST(Strategys, TitForTatAnger1) {
	mode = "IsNotSet";
	pointS1 = pointS2 = pointS3 = steps = countTournament = 0;
	strategys.clear();
	moveTA = true;
	char* argv[] = { "prog", "titfortatanger", "traitor", "backandforth", "fast" };
	int res = Game(5, argv);
	EXPECT_EQ(strategys[0]->getName(), "TitForTatAnger");
	EXPECT_EQ(strategys[1]->getName(), "Traitor");
	EXPECT_EQ(strategys[2]->getName(), "BackAndForth");
	EXPECT_TRUE(moveTA);
}

TEST(Strategys, TitForTatAnger2) {
	mode = "IsNotSet";
	pointS1 = pointS2 = pointS3 = steps = countTournament = 0;
	strategys.clear();
	moveTA = true;
	char* argv[] = { "prog", "titfortatanger", "kind", "backandforth", "fast" };
	int res = Game(5, argv);
	EXPECT_EQ(strategys[0]->getName(), "TitForTatAnger");
	EXPECT_EQ(strategys[1]->getName(), "Kind");
	EXPECT_EQ(strategys[2]->getName(), "BackAndForth");
	EXPECT_TRUE(moveTA);
}
