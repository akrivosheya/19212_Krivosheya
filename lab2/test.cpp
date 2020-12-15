#include "pch.h"
#include "Game.h"
#include "Preparation.h"
#include "Display.h"
#include <iostream>

Display D;

int Launch(int argc, char* argv[], Game** G) {
	if (argc < 4) return -1;
	Preparation P;
	*G = P.Prepare(argc, argv);
	if (!(*G)) {
		return -1;
	}
	Printer Print;
	(*G)->Play("M.txt", Print);
	return 0;
}

TEST(Options, STFTfast) {
	char* argv[] = { "prog", "southback", "traitor", "backandforth", "fast", "50" };
	Game* G = nullptr;
	int res = Launch(6, argv, &G);
	EXPECT_EQ(res, 0);
	EXPECT_EQ(D.GetName(G), "Fast");
	EXPECT_EQ(D.GetSteps(G), 50);
	EXPECT_EQ(D.GetStrategys(G)[0]->getName(), "SouthBack");
	EXPECT_EQ(D.GetStrategys(G)[1]->getName(), "Traitor");
	EXPECT_EQ(D.GetStrategys(G)[2]->getName(), "BackAndForth");
	delete G;
}
TEST(Options, Fast50) {
	char* argv[] = { "prog", "kind", "traitor", "backandforth", "fast", "50" };
	Game* G = nullptr;
	int res = Launch(6, argv, &G);
	EXPECT_EQ(res, 0);
	EXPECT_EQ(D.GetName(G), "Fast");
	EXPECT_EQ(D.GetSteps(G), 50);
	EXPECT_EQ(D.GetStrategys(G)[0]->getName(), "Kind");
	EXPECT_EQ(D.GetStrategys(G)[1]->getName(), "Traitor");
	EXPECT_EQ(D.GetStrategys(G)[2]->getName(), "BackAndForth");
	delete G;
}

TEST(Options, Fast) {
	char* argv[] = { "prog", "kind", "traitor", "backandforth", "fast" };
	Game* G = nullptr;
	int res = Launch(5, argv, &G);
	EXPECT_EQ(res, 0);
	EXPECT_EQ(D.GetName(G), "Fast");
	EXPECT_EQ(D.GetSteps(G), 100);
	EXPECT_EQ(D.GetStrategys(G)[0]->getName(), "Kind");
	EXPECT_EQ(D.GetStrategys(G)[1]->getName(), "Traitor");
	EXPECT_EQ(D.GetStrategys(G)[2]->getName(), "BackAndForth");
	delete G;
}

TEST(Options, Detailed150) {
	char* argv[] = { "prog", "southtitfortat", "titfortatkind", "titfortatanger", "detailed", "150" };
	Game* G = nullptr;
	int res = Launch(6, argv, &G);
	EXPECT_EQ(res, 0);
	EXPECT_EQ(D.GetName(G), "Detailed");
	EXPECT_EQ(D.GetSteps(G), 150);
	EXPECT_EQ(D.GetStrategys(G)[0]->getName(), "SouthTitForTat");
	EXPECT_EQ(D.GetStrategys(G)[1]->getName(), "TitForTatKind");
	EXPECT_EQ(D.GetStrategys(G)[2]->getName(), "TitForTatAnger");
	delete G;
}

TEST(Options, Tournament90) {
	char* argv[] = { "prog", "kind", "traitor", "backandforth", "southback", "titfortatkind", "titfortatanger", "tournament", "90" };
	Game* G = nullptr;
	int res = Launch(9, argv, &G);
	EXPECT_EQ(res, 0);
	EXPECT_EQ(D.GetName(G), "Tournament");
	EXPECT_EQ(D.GetSteps(G), 90);
	EXPECT_EQ(D.GetStrategys(G)[0]->getName(), "Kind");
	EXPECT_EQ(D.GetStrategys(G)[1]->getName(), "Traitor");
	EXPECT_EQ(D.GetStrategys(G)[2]->getName(), "BackAndForth");
	EXPECT_EQ(D.GetStrategys(G)[3]->getName(), "SouthBack");
	EXPECT_EQ(D.GetStrategys(G)[4]->getName(), "TitForTatKind");
	EXPECT_EQ(D.GetStrategys(G)[5]->getName(), "TitForTatAnger");
	EXPECT_EQ(D.GetTournamentCount(G), 6 * 5 * 4 / 3 / 2);
	delete G;
}

TEST(Options, OptionalDetailed) {
	char* argv[] = { "prog", "southback", "southback", "titfortatanger" };
	Game* G = nullptr;
	int res = Launch(4, argv, &G);
	EXPECT_EQ(res, 0);
	EXPECT_EQ(D.GetName(G), "Detailed");
	EXPECT_EQ(D.GetSteps(G), 100);
	EXPECT_EQ(D.GetStrategys(G)[0]->getName(), "SouthBack");
	EXPECT_EQ(D.GetStrategys(G)[1]->getName(), "SouthBack");
	EXPECT_EQ(D.GetStrategys(G)[2]->getName(), "TitForTatAnger");
	delete G;
}

TEST(Options, OptionalTournament60) {
	char* argv[] = { "prog", "southback", "southback", "titfortatanger", "traitor", "southtitfortat", "60" };
	Game* G = nullptr;
	int res = Launch(7, argv, &G);
	EXPECT_EQ(res, 0);
	EXPECT_EQ(D.GetName(G), "Tournament");
	EXPECT_EQ(D.GetSteps(G), 60);
	EXPECT_EQ(D.GetStrategys(G)[0]->getName(), "SouthBack");
	EXPECT_EQ(D.GetStrategys(G)[1]->getName(), "SouthBack");
	EXPECT_EQ(D.GetStrategys(G)[2]->getName(), "TitForTatAnger");
	EXPECT_EQ(D.GetStrategys(G)[3]->getName(), "Traitor");
	EXPECT_EQ(D.GetStrategys(G)[4]->getName(), "SouthTitForTat");
	EXPECT_EQ(D.GetTournamentCount(G), 5 * 4 / 2);
	delete G;
}

TEST(Options, OptionalTournament) {
	char* argv[] = { "prog", "southback", "southback", "titfortatanger", "traitor", "southtitfortat", "kind" };
	Game* G = nullptr;
	int res = Launch(7, argv, &G);
	EXPECT_EQ(res, 0);
	EXPECT_EQ(D.GetName(G), "Tournament");
	EXPECT_EQ(D.GetSteps(G), 100);
	EXPECT_EQ(D.GetStrategys(G)[0]->getName(), "SouthBack");
	EXPECT_EQ(D.GetStrategys(G)[1]->getName(), "SouthBack");
	EXPECT_EQ(D.GetStrategys(G)[2]->getName(), "TitForTatAnger");
	EXPECT_EQ(D.GetStrategys(G)[3]->getName(), "Traitor");
	EXPECT_EQ(D.GetStrategys(G)[4]->getName(), "SouthTitForTat");
	EXPECT_EQ(D.GetStrategys(G)[5]->getName(), "Kind");
	EXPECT_EQ(D.GetTournamentCount(G), 6 * 5 * 4 / 3 / 2);
	delete G;
}

TEST(Options, FewArgc) {
	char* argv[] = { "prog", "southback", "kind" };
	Game* G = nullptr;
	int res = Launch(3, argv, &G);
	EXPECT_EQ(res, -1);
	delete G;
}

TEST(Options, FewStrategys1) {
	char* argv[] = { "prog", "southback", "kind", "detailed" };
	Game* G = nullptr;
	int res = Launch(4, argv, &G);
	EXPECT_EQ(res, -1);
}

TEST(Options, NotRealStrategy) {
	char* argv[] = { "prog", "southtitfortat", "kind", "blablabla", "traitor" };
	Game* G = nullptr;
	int res = Launch(5, argv, &G);
	EXPECT_EQ(res, -1);
	delete G;
}

TEST(Strategys, SouthBack) {
	char* argv[] = { "prog", "southback", "southback", "traitor", "fast" };
	Game* G = nullptr;
	int res = Launch(5, argv, &G);
	EXPECT_EQ(D.GetStrategys(G)[0]->getName(), "SouthBack");
	EXPECT_EQ(D.GetStrategys(G)[1]->getName(), "SouthBack");
	EXPECT_TRUE(D.GetTraitor1(G) || D.GetTraitor2(G));
	EXPECT_TRUE(D.GetKind2(G) || D.GetKind1(G));
	delete G;
}

TEST(Strategys, SouthTitForTat) {
	char* argv[] = { "prog", "southtitfortat", "southtitfortat", "backandforth", "fast" };
	Game* G = nullptr;
	int res = Launch(5, argv, &G);
	EXPECT_EQ(D.GetStrategys(G)[0]->getName(), "SouthTitForTat");
	EXPECT_EQ(D.GetStrategys(G)[1]->getName(), "SouthTitForTat");
	EXPECT_TRUE(D.GetTraitor1(G) || D.GetTraitor2(G));
	EXPECT_TRUE(D.GetKind2(G) || D.GetKind1(G));
	delete G;
}

TEST(Strategys, SouthDifferent1) {
	char* argv[] = { "prog", "southback", "southtitfortat", "backandforth", "fast" };
	Game* G = nullptr;
	int res = Launch(5, argv, &G);
	EXPECT_EQ(D.GetStrategys(G)[0]->getName(), "SouthBack");
	EXPECT_EQ(D.GetStrategys(G)[1]->getName(), "SouthTitForTat");
	EXPECT_TRUE(D.GetTraitor1(G) || D.GetTraitor2(G));
	EXPECT_TRUE(D.GetKind2(G) || D.GetKind1(G));
	delete G;
}

TEST(Strategys, SouthDifferent2) {
	char* argv[] = { "prog", "southtitfortat", "southback", "backandforth", "fast" };
	Game* G = nullptr;
	int res = Launch(5, argv, &G);
	EXPECT_EQ(D.GetStrategys(G)[0]->getName(), "SouthTitForTat");
	EXPECT_EQ(D.GetStrategys(G)[1]->getName(), "SouthBack");
	EXPECT_TRUE(D.GetTraitor1(G) || D.GetTraitor2(G));
	EXPECT_TRUE(D.GetKind2(G) || D.GetKind1(G));
	delete G;
}

TEST(Strategys, KindTraitorBackAndForth) {
	char* argv[] = { "prog", "traitor", "kind", "backandforth", "fast" };
	Game* G = nullptr;
	int res = Launch(5, argv, &G);
	EXPECT_EQ(D.GetStrategys(G)[0]->getName(), "Traitor");
	EXPECT_EQ(D.GetStrategys(G)[1]->getName(), "Kind");
	EXPECT_EQ(D.GetStrategys(G)[2]->getName(), "BackAndForth");
	EXPECT_TRUE(D.GetTraitor1(G));
	EXPECT_TRUE(D.GetKind2(G));
	EXPECT_TRUE(D.GetBackAndForth3(G));
	delete G;
}

TEST(Strategys, TitForTatKind1) {
	char* argv[] = { "prog", "kind", "titfortatkind", "backandforth", "fast" };
	Game* G = nullptr;
	int res = Launch(5, argv, &G);
	EXPECT_EQ(D.GetStrategys(G)[0]->getName(), "Kind");
	EXPECT_EQ(D.GetStrategys(G)[1]->getName(), "TitForTatKind");
	EXPECT_EQ(D.GetStrategys(G)[2]->getName(), "BackAndForth");
	EXPECT_TRUE(D.GetKind2(G));
	delete G;
}

TEST(Strategys, TitForTatKind2) {
	char* argv[] = { "prog", "titfortatkind", "traitor", "backandforth", "fast" };
	Game* G = nullptr;
	int res = Launch(5, argv, &G);
	EXPECT_EQ(D.GetStrategys(G)[0]->getName(), "TitForTatKind");
	EXPECT_EQ(D.GetStrategys(G)[1]->getName(), "Traitor");
	EXPECT_EQ(D.GetStrategys(G)[2]->getName(), "BackAndForth");
	EXPECT_TRUE(D.GetTitForTat1(G));
	delete G;
}

TEST(Strategys, TitForTatAnger1) {
	char* argv[] = { "prog", "titfortatanger", "traitor", "backandforth", "fast" };
	Game* G = nullptr;
	int res = Launch(5, argv, &G);
	EXPECT_EQ(D.GetStrategys(G)[0]->getName(), "TitForTatAnger");
	EXPECT_EQ(D.GetStrategys(G)[1]->getName(), "Traitor");
	EXPECT_EQ(D.GetStrategys(G)[2]->getName(), "BackAndForth");
	EXPECT_TRUE(D.GetTraitor1(G));
	delete G;
}

TEST(Strategys, TitForTatAnger2) {
	char* argv[] = { "prog", "titfortatanger", "kind", "backandforth", "fast" };
	Game* G = nullptr;
	int res = Launch(5, argv, &G);
	EXPECT_EQ(D.GetStrategys(G)[0]->getName(), "TitForTatAnger");
	EXPECT_EQ(D.GetStrategys(G)[1]->getName(), "Kind");
	EXPECT_EQ(D.GetStrategys(G)[2]->getName(), "BackAndForth");
	EXPECT_TRUE(D.GetTitForTat1(G));
	delete G;
}

TEST(Points, points1) {
	char* argv[] = { "prog", "kind", "traitor", "backandforth", "fast" };
	Game* G = nullptr;
	int res = Launch(5, argv, &G);
	EXPECT_EQ(D.GetStrategys(G)[0]->getName(), "Kind");
	EXPECT_EQ(D.GetStrategys(G)[1]->getName(), "Traitor");
	EXPECT_EQ(D.GetStrategys(G)[2]->getName(), "BackAndForth");
	EXPECT_EQ(D.GetPoint(1, G), 150);
	EXPECT_EQ(D.GetPoint(2, G), 700);
	EXPECT_EQ(D.GetPoint(3, G), 400);
	delete G;
}

TEST(Points, points2) {
	char* argv[] = { "prog", "titfortatanger", "kind", "backandforth", "fast" };
	Game* G = nullptr;
	int res = Launch(5, argv, &G);
	EXPECT_EQ(D.GetStrategys(G)[0]->getName(), "TitForTatAnger");
	EXPECT_EQ(D.GetStrategys(G)[1]->getName(), "Kind");
	EXPECT_EQ(D.GetStrategys(G)[2]->getName(), "BackAndForth");
	EXPECT_EQ(D.GetPoint(1, G), 602);
	EXPECT_EQ(D.GetPoint(2, G), 297);
	EXPECT_EQ(D.GetPoint(3, G), 596);
	delete G;
}

TEST(Points, points3) {
	char* argv[] = { "prog", "traitor", "titfortatkind", "backandforth", "fast" };
	Game* G = nullptr;
	int res = Launch(5, argv, &G);
	EXPECT_EQ(D.GetStrategys(G)[0]->getName(), "Traitor");
	EXPECT_EQ(D.GetStrategys(G)[1]->getName(), "TitForTatKind");
	EXPECT_EQ(D.GetStrategys(G)[2]->getName(), "BackAndForth");
	EXPECT_EQ(D.GetPoint(1, G), 496);
	EXPECT_EQ(D.GetPoint(2, G), 251);
	EXPECT_EQ(D.GetPoint(3, G), 246);
	delete G;
}
