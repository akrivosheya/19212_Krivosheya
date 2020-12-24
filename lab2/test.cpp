#include "Game.h"
#include "Preparation.h"
#include "Display.h"

Game* Launch(int argc, char* argv[], int& res) {
	if (argc < 4) { 
		res = -1;
		return nullptr; 
	}
	Preparation P;
	std::unique_ptr<Game> G(P.Prepare(argc, argv));
	if (!G.get()) {
		res = -1;
		return nullptr;
	}
	Printer Print;
	std::ifstream file;
	file.open("Matrix.txt");
	G->SetRules(file);
	G->Play(Print);
	res = 0;
	return G.release();
}

class TestGame : public ::testing::Test {
protected:
	Display D;
	int res;
	std::unique_ptr<Game> G;
};

TEST(op, pf) {
	EXPECT_TRUE(true);
}

TEST_F(TestGame, Southfast) {
	char* argv[] = { "prog", "southback", "traitor", "backandforth", 
		"fast", "50" };
	G.reset(Launch(6, argv, res));
	EXPECT_EQ(res, 0);
	EXPECT_EQ(D.GetName(G.get()), "Fast");
	EXPECT_EQ(D.GetSteps(G.get()), 50);
	EXPECT_EQ(D.GetStrategys(G.get())[0]->getName(), "SouthBack");
	EXPECT_EQ(D.GetStrategys(G.get())[1]->getName(), "Traitor");
	EXPECT_EQ(D.GetStrategys(G.get())[2]->getName(), "BackAndForth");
}

TEST_F(TestGame, Fast50) {
	char* argv[] = { "prog", "kind", "traitor", "backandforth", "fast", "50" };
	G.reset(Launch(6, argv, res));
	EXPECT_EQ(res, 0);
	EXPECT_EQ(D.GetName(G.get()), "Fast");
	EXPECT_EQ(D.GetSteps(G.get()), 50);
	EXPECT_EQ(D.GetStrategys(G.get())[0]->getName(), "Kind");
	EXPECT_EQ(D.GetStrategys(G.get())[1]->getName(), "Traitor");
	EXPECT_EQ(D.GetStrategys(G.get())[2]->getName(), "BackAndForth");
}

TEST_F(TestGame, Fast) {
	char* argv[] = { "prog", "kind", "traitor", "backandforth", "fast" };
	G.reset(Launch(5, argv, res));
	EXPECT_EQ(res, 0);
	EXPECT_EQ(D.GetName(G.get()), "Fast");
	EXPECT_EQ(D.GetSteps(G.get()), 100);
	EXPECT_EQ(D.GetStrategys(G.get())[0]->getName(), "Kind");
	EXPECT_EQ(D.GetStrategys(G.get())[1]->getName(), "Traitor");
	EXPECT_EQ(D.GetStrategys(G.get())[2]->getName(), "BackAndForth");
}

TEST_F(TestGame, Detailed150) {
	char* argv[] = { "prog", "southtitfortat", "titfortatkind", 
		"titfortatanger", "detailed", "150" };
	G.reset(Launch(6, argv, res));
	EXPECT_EQ(res, 0);
	EXPECT_EQ(D.GetName(G.get()), "Detailed");
	EXPECT_EQ(D.GetSteps(G.get()), 150);
	EXPECT_EQ(D.GetStrategys(G.get())[0]->getName(), "SouthTitForTat");
	EXPECT_EQ(D.GetStrategys(G.get())[1]->getName(), "TitForTatKind");
	EXPECT_EQ(D.GetStrategys(G.get())[2]->getName(), "TitForTatAnger");
}

TEST_F(TestGame, Tournament90) {
	char* argv[] = { "prog", "kind", "backandforth", "traitor", 
		"southback", "titfortatkind", "titfortatanger", "tournament", "90" };
	G.reset(Launch(9, argv, res));
	EXPECT_EQ(res, 0);
	EXPECT_EQ(D.GetName(G.get()), "Tournament");
	EXPECT_EQ(D.GetSteps(G.get()), 90);
	EXPECT_EQ(D.GetStrategys(G.get())[0]->getName(), "Kind");
	EXPECT_EQ(D.GetStrategys(G.get())[1]->getName(), "BackAndForth");
	EXPECT_EQ(D.GetStrategys(G.get())[2]->getName(), "Traitor");
	EXPECT_EQ(D.GetStrategys(G.get())[3]->getName(), "SouthBack");
	EXPECT_EQ(D.GetStrategys(G.get())[4]->getName(), "TitForTatKind");
	EXPECT_EQ(D.GetStrategys(G.get())[5]->getName(), "TitForTatAnger");
	EXPECT_EQ(D.GetTournamentCount(G.get()), 6 * 5 * 4 / 3 / 2);
}

TEST_F(TestGame, OptionalDetailed) {
	char* argv[] = { "prog", "southback", "southback", "titfortatanger" };
	G.reset(Launch(4, argv, res));
	EXPECT_EQ(res, 0);
	EXPECT_EQ(D.GetName(G.get()), "Detailed");
	EXPECT_EQ(D.GetSteps(G.get()), 100);
	EXPECT_EQ(D.GetStrategys(G.get())[0]->getName(), "SouthBack");
	EXPECT_EQ(D.GetStrategys(G.get())[1]->getName(), "SouthBack");
	EXPECT_EQ(D.GetStrategys(G.get())[2]->getName(), "TitForTatAnger");
}

TEST_F(TestGame, OptionalTournament60) {
	char* argv[] = { "prog", "southback", "southback", "titfortatanger", 
		"traitor", "southtitfortat", "60" };
	G.reset(Launch(7, argv, res));
	EXPECT_EQ(res, 0);
	EXPECT_EQ(D.GetName(G.get()), "Tournament");
	EXPECT_EQ(D.GetSteps(G.get()), 60);
	EXPECT_EQ(D.GetStrategys(G.get())[0]->getName(), "SouthBack");
	EXPECT_EQ(D.GetStrategys(G.get())[1]->getName(), "SouthBack");
	EXPECT_EQ(D.GetStrategys(G.get())[2]->getName(), "TitForTatAnger");
	EXPECT_EQ(D.GetStrategys(G.get())[3]->getName(), "Traitor");
	EXPECT_EQ(D.GetStrategys(G.get())[4]->getName(), "SouthTitForTat");
	EXPECT_EQ(D.GetTournamentCount(G.get()), 5 * 4 / 2);
}

TEST_F(TestGame, OptionalTournament) {
	char* argv[] = { "prog", "southback", "southback", "titfortatanger",
		"traitor", "southtitfortat", "kind" };
	G.reset(Launch(7, argv, res));
	EXPECT_EQ(res, 0);
	EXPECT_EQ(D.GetName(G.get()), "Tournament");
	EXPECT_EQ(D.GetSteps(G.get()), 100);
	EXPECT_EQ(D.GetStrategys(G.get())[0]->getName(), "SouthBack");
	EXPECT_EQ(D.GetStrategys(G.get())[1]->getName(), "SouthBack");
	EXPECT_EQ(D.GetStrategys(G.get())[2]->getName(), "TitForTatAnger");
	EXPECT_EQ(D.GetStrategys(G.get())[3]->getName(), "Traitor");
	EXPECT_EQ(D.GetStrategys(G.get())[4]->getName(), "SouthTitForTat");
	EXPECT_EQ(D.GetStrategys(G.get())[5]->getName(), "Kind");
	EXPECT_EQ(D.GetTournamentCount(G.get()), 6 * 5 * 4 / 3 / 2);
}

TEST_F(TestGame, FewArgc) {
	char* argv[] = { "prog", "southback", "kind" };
	G.reset(Launch(3, argv, res));
	EXPECT_EQ(res, -1);
}

TEST_F(TestGame, FewStrategys1) {
	char* argv[] = { "prog", "southback", "kind", "detailed" };
	G.reset(Launch(4, argv, res));
	EXPECT_EQ(res, -1);
}

TEST_F(TestGame, NotRealStrategy) {
	char* argv[] = { "prog", "southtitfortat", "kind", 
		"blablabla", "traitor" };
	G.reset(Launch(5, argv, res));
	EXPECT_EQ(res, -1);
}

TEST_F(TestGame, SouthBack) {
	char* argv[] = { "prog", "southback", "southback", "traitor", "fast" };
	G.reset(Launch(5, argv, res));
	EXPECT_EQ(D.GetStrategys(G.get())[0]->getName(), "SouthBack");
	EXPECT_EQ(D.GetStrategys(G.get())[1]->getName(), "SouthBack");
	EXPECT_TRUE(D.GetTraitor1(G.get()) || D.GetTraitor2(G.get()));
	EXPECT_TRUE(D.GetKind2(G.get()) || D.GetKind1(G.get()));
}

TEST_F(TestGame, SouthTitForTat) {
	char* argv[] = { "prog", "southtitfortat", "southtitfortat", 
		"backandforth", "fast" };
	G.reset(Launch(5, argv, res));
	EXPECT_EQ(D.GetStrategys(G.get())[0]->getName(), "SouthTitForTat");
	EXPECT_EQ(D.GetStrategys(G.get())[1]->getName(), "SouthTitForTat");
	EXPECT_TRUE(D.GetTraitor1(G.get()) || D.GetTraitor2(G.get()));
	EXPECT_TRUE(D.GetKind2(G.get()) || D.GetKind1(G.get()));
}

TEST_F(TestGame, SouthDifferent1) {
	char* argv[] = { "prog", "southback", "southtitfortat", 
		"backandforth", "fast" };
	G.reset(Launch(5, argv, res));
	EXPECT_EQ(D.GetStrategys(G.get())[0]->getName(), "SouthBack");
	EXPECT_EQ(D.GetStrategys(G.get())[1]->getName(), "SouthTitForTat");
	EXPECT_TRUE(D.GetTraitor1(G.get()) || D.GetTraitor2(G.get()));
	EXPECT_TRUE(D.GetKind2(G.get()) || D.GetKind1(G.get()));
}

TEST_F(TestGame, SouthDifferent2) {
	char* argv[] = { "prog", "southtitfortat", "southback", 
		"backandforth", "fast" };
	G.reset(Launch(5, argv, res));
	EXPECT_EQ(D.GetStrategys(G.get())[0]->getName(), "SouthTitForTat");
	EXPECT_EQ(D.GetStrategys(G.get())[1]->getName(), "SouthBack");
	EXPECT_TRUE(D.GetTraitor1(G.get()) || D.GetTraitor2(G.get()));
	EXPECT_TRUE(D.GetKind2(G.get()) || D.GetKind1(G.get()));
}

TEST_F(TestGame, KindTraitorBackAndForth) {
	char* argv[] = { "prog", "traitor", "kind", "backandforth", "fast" };
	G.reset(Launch(5, argv, res));
	EXPECT_EQ(D.GetStrategys(G.get())[0]->getName(), "Traitor");
	EXPECT_EQ(D.GetStrategys(G.get())[1]->getName(), "Kind");
	EXPECT_EQ(D.GetStrategys(G.get())[2]->getName(), "BackAndForth");
	EXPECT_TRUE(D.GetTraitor1(G.get()));
	EXPECT_TRUE(D.GetKind2(G.get()));
	EXPECT_TRUE(D.GetBackAndForth3(G.get()));
}

TEST_F(TestGame, TitForTatKind1) {
	char* argv[] = { "prog", "kind", "titfortatkind", "backandforth", "fast" };
	G.reset(Launch(5, argv, res));
	EXPECT_EQ(D.GetStrategys(G.get())[0]->getName(), "Kind");
	EXPECT_EQ(D.GetStrategys(G.get())[1]->getName(), "TitForTatKind");
	EXPECT_EQ(D.GetStrategys(G.get())[2]->getName(), "BackAndForth");
	EXPECT_TRUE(D.GetKind2(G.get()));
}

TEST_F(TestGame, TitForTatKind2) {
	char* argv[] = { "prog", "titfortatkind", "traitor", 
		"backandforth", "fast" };
	G.reset(Launch(5, argv, res));
	EXPECT_EQ(D.GetStrategys(G.get())[0]->getName(), "TitForTatKind");
	EXPECT_EQ(D.GetStrategys(G.get())[1]->getName(), "Traitor");
	EXPECT_EQ(D.GetStrategys(G.get())[2]->getName(), "BackAndForth");
	EXPECT_TRUE(D.GetTitForTat1(G.get()));
}

TEST_F(TestGame, TitForTatAnger1) {
	char* argv[] = { "prog", "titfortatanger", "traitor", 
		"backandforth", "fast" };
	G.reset(Launch(5, argv, res));
	EXPECT_EQ(D.GetStrategys(G.get())[0]->getName(), "TitForTatAnger");
	EXPECT_EQ(D.GetStrategys(G.get())[1]->getName(), "Traitor");
	EXPECT_EQ(D.GetStrategys(G.get())[2]->getName(), "BackAndForth");
	EXPECT_TRUE(D.GetTraitor1(G.get()));
}

TEST_F(TestGame, TitForTatAnger2) {
	char* argv[] = { "prog", "titfortatanger", "kind", 
		"backandforth", "fast" };
	G.reset(Launch(5, argv, res));
	EXPECT_EQ(D.GetStrategys(G.get())[0]->getName(), "TitForTatAnger");
	EXPECT_EQ(D.GetStrategys(G.get())[1]->getName(), "Kind");
	EXPECT_EQ(D.GetStrategys(G.get())[2]->getName(), "BackAndForth");
	EXPECT_TRUE(D.GetTitForTat1(G.get()));
}

TEST_F(TestGame, points1) {
	char* argv[] = { "prog", "kind", "traitor", "backandforth", "fast" };
	G.reset(Launch(5, argv, res));
	EXPECT_EQ(D.GetStrategys(G.get())[0]->getName(), "Kind");
	EXPECT_EQ(D.GetStrategys(G.get())[1]->getName(), "Traitor");
	EXPECT_EQ(D.GetStrategys(G.get())[2]->getName(), "BackAndForth");
	EXPECT_EQ(D.GetPoint(G.get())[0], 150);
	EXPECT_EQ(D.GetPoint(G.get())[1], 700);
	EXPECT_EQ(D.GetPoint(G.get())[2], 400);
}

TEST_F(TestGame, points2) {
	char* argv[] = { "prog", "titfortatanger", "kind", 
		"backandforth", "fast" };
	G.reset(Launch(5, argv, res));
	EXPECT_EQ(D.GetStrategys(G.get())[0]->getName(), "TitForTatAnger");
	EXPECT_EQ(D.GetStrategys(G.get())[1]->getName(), "Kind");
	EXPECT_EQ(D.GetStrategys(G.get())[2]->getName(), "BackAndForth");
	EXPECT_EQ(D.GetPoint(G.get())[0], 602);
	EXPECT_EQ(D.GetPoint(G.get())[1], 297);
	EXPECT_EQ(D.GetPoint(G.get())[2], 596);
}

TEST_F(TestGame, points3) {
	char* argv[] = { "prog", "traitor", "titfortatkind", 
		"backandforth", "fast" };
	G.reset(Launch(5, argv, res));
	EXPECT_EQ(D.GetStrategys(G.get())[0]->getName(), "Traitor");
	EXPECT_EQ(D.GetStrategys(G.get())[1]->getName(), "TitForTatKind");
	EXPECT_EQ(D.GetStrategys(G.get())[2]->getName(), "BackAndForth");
	EXPECT_EQ(D.GetPoint(G.get())[0], 496);
	EXPECT_EQ(D.GetPoint(G.get())[1], 251);
	EXPECT_EQ(D.GetPoint(G.get())[2], 246);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	int j, i = RUN_ALL_TESTS();
	return i;
}
