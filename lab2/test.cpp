#include "pch.h"
#include "Launcher.h"
#include "SouthWinner.h"

std::string mode = "IsNotSet";
int steps = 0;
std::vector<Strategy*> strategys;



TEST(Options, STFTfast) {
	SouthWinner::Reset();
	mode = "IsNotSet";
	steps = 0;
	strategys.clear();
	char* argv[] = { "prog", "stft", "traitor", "backandforth", "fast", "50" };
	Launcher L;
	int res = L.Launch(6, argv, mode, steps, strategys);
	EXPECT_EQ(res, 0);
	EXPECT_EQ(mode, "fast");
	EXPECT_EQ(steps, 50);
	EXPECT_EQ(strategys[0]->getName(), "STFT");
	EXPECT_EQ(strategys[1]->getName(), "Traitor");
	EXPECT_EQ(strategys[2]->getName(), "BackAndForth");
}
TEST(Options, Fast50) {
	SouthWinner::Reset();
	mode = "IsNotSet";
	steps = 0;
	strategys.clear();
	char* argv[] = { "prog", "kind", "traitor", "backandforth", "fast", "50" };
	Launcher L;
	int res = L.Launch(6, argv, mode, steps, strategys);
	EXPECT_EQ(res, 0);
	EXPECT_EQ(mode, "fast");
	EXPECT_EQ(steps, 50);
	EXPECT_EQ(strategys[0]->getName(), "Kind");
	EXPECT_EQ(strategys[1]->getName(), "Traitor");
	EXPECT_EQ(strategys[2]->getName(), "BackAndForth");
}

TEST(Options, Fast) {
	SouthWinner::Reset();
	mode = "IsNotSet";
	steps = 0;
	strategys.clear();
	char* argv[] = { "prog", "kind", "traitor", "backandforth", "fast" };
	Launcher L;
	int res = L.Launch(5, argv, mode, steps, strategys);
	EXPECT_EQ(res, 0);
	EXPECT_EQ(mode, "fast");
	EXPECT_EQ(steps, 100);
	EXPECT_EQ(strategys[0]->getName(), "Kind");
	EXPECT_EQ(strategys[1]->getName(), "Traitor");
	EXPECT_EQ(strategys[2]->getName(), "BackAndForth");
}

TEST(Options, Detailed150) {
	SouthWinner::Reset();
	mode = "IsNotSet";
	steps = 0;
	strategys.clear();
	char* argv[] = { "prog", "southampton", "titfortatkind", "titfortatanger", "detailed", "150" };
	Launcher L;
	int res = L.Launch(6, argv, mode, steps, strategys);
	EXPECT_EQ(res, 0);
	EXPECT_EQ(mode, "detailed");
	EXPECT_EQ(steps, 150);
	EXPECT_EQ(strategys[0]->getName(), "Southampton");
	EXPECT_EQ(strategys[1]->getName(), "TitForTatKind");
	EXPECT_EQ(strategys[2]->getName(), "TitForTatAnger");
}

TEST(Options, Tournament90) {
	SouthWinner::Reset();
	mode = "IsNotSet";
	steps = 0;
	strategys.clear();
	char* argv[] = { "prog", "kind", "traitor", "backandforth", "southampton", "titfortatkind", "titfortatanger", "tournament", "90" };
	Launcher L;
	int res = L.Launch(9, argv, mode, steps, strategys);
	EXPECT_EQ(res, 0);
	EXPECT_EQ(mode, "tournament");
	EXPECT_EQ(steps, 90);
	EXPECT_EQ(strategys[0]->getName(), "Kind");
	EXPECT_EQ(strategys[1]->getName(), "Traitor");
	EXPECT_EQ(strategys[2]->getName(), "BackAndForth");
	EXPECT_EQ(strategys[3]->getName(), "Southampton");
	EXPECT_EQ(strategys[4]->getName(), "TitForTatKind");
	EXPECT_EQ(strategys[5]->getName(), "TitForTatAnger");
	EXPECT_EQ(L.GetCount(), 6 * 5 * 4 / 3 / 2);
}

TEST(Options, OptionalDetailed) {
	SouthWinner::Reset();
	mode = "IsNotSet";
	steps = 0;
	strategys.clear();
	char* argv[] = { "prog", "southampton", "southampton", "titfortatanger" };
	Launcher L;
	int res = L.Launch(4, argv, mode, steps, strategys);
	EXPECT_EQ(res, 0);
	EXPECT_EQ(mode, "detailed");
	EXPECT_EQ(steps, 100);
	EXPECT_EQ(strategys[0]->getName(), "Southampton");
	EXPECT_EQ(strategys[1]->getName(), "Southampton");
	EXPECT_EQ(strategys[2]->getName(), "TitForTatAnger");
}

TEST(Options, OptionalTournament60) {
	SouthWinner::Reset();
	mode = "IsNotSet";
	steps = 0;
	strategys.clear();
	char* argv[] = { "prog", "southampton", "southampton", "titfortatanger", "traitor", "stft", "60" };
	Launcher L;
	int res = L.Launch(7, argv, mode, steps, strategys);
	EXPECT_EQ(res, 0);
	EXPECT_EQ(mode, "tournament");
	EXPECT_EQ(steps, 60);
	EXPECT_EQ(strategys[0]->getName(), "Southampton");
	EXPECT_EQ(strategys[1]->getName(), "Southampton");
	EXPECT_EQ(strategys[2]->getName(), "TitForTatAnger");
	EXPECT_EQ(strategys[3]->getName(), "Traitor");
	EXPECT_EQ(strategys[4]->getName(), "STFT");
	EXPECT_EQ(L.GetCount(), 5 * 4 / 2);
}

TEST(Options, OptionalTournament) {
	SouthWinner::Reset();
	mode = "IsNotSet";
	steps = 0;
	strategys.clear();
	char* argv[] = { "prog", "southampton", "southampton", "titfortatanger", "traitor", "stft", "kind" };
	Launcher L;
	int res = L.Launch(7, argv, mode, steps, strategys);
	EXPECT_EQ(res, 0);
	EXPECT_EQ(mode, "tournament");
	EXPECT_EQ(steps, 100);
	EXPECT_EQ(strategys[0]->getName(), "Southampton");
	EXPECT_EQ(strategys[1]->getName(), "Southampton");
	EXPECT_EQ(strategys[2]->getName(), "TitForTatAnger");
	EXPECT_EQ(strategys[3]->getName(), "Traitor");
	EXPECT_EQ(strategys[4]->getName(), "STFT");
	EXPECT_EQ(strategys[5]->getName(), "Kind");
	EXPECT_EQ(L.GetCount(), 6 * 5 * 4 / 3 / 2);
}

TEST(Options, FewArgc) {
	SouthWinner::Reset();
	mode = "IsNotSet";
	steps = 0;
	strategys.clear();
	char* argv[] = { "prog", "southampton", "kind" };
	Launcher L;
	int res = L.Launch(3, argv, mode, steps, strategys);
	EXPECT_EQ(res, -1);
}

TEST(Options, FewStrategys1) {
	SouthWinner::Reset();
	mode = "IsNotSet";
	steps = 0;
	strategys.clear();
	char* argv[] = { "prog", "southampton", "kind", "detailed"};
	Launcher L;
	int res = L.Launch(4, argv, mode, steps, strategys);
	EXPECT_EQ(res, -1);
}

TEST(Options, NotRealStrategy) {
	SouthWinner::Reset();
	mode = "IsNotSet";
	steps = 0;
	strategys.clear();
	char* argv[] = { "prog", "stft", "kind", "blablabla", "traitor" };
	Launcher L;
	int res = L.Launch(5, argv, mode, steps, strategys);
	EXPECT_EQ(res, -1);
}

TEST(Strategys, Southampton) {
	SouthWinner::Reset();
	mode = "IsNotSet";
	steps = 0;
	strategys.clear();
	char* argv[] = { "prog", "southampton", "southampton", "traitor", "fast" };
	Launcher L;
	int res = L.Launch(5, argv, mode, steps, strategys);
	EXPECT_EQ(strategys[0]->getName(), "Southampton");
	EXPECT_EQ(strategys[1]->getName(), "Southampton");
	EXPECT_TRUE(L.GetSouth1());
	EXPECT_TRUE(L.GetSouth2());
}

TEST(Strategys, STFT) {
	SouthWinner::Reset();
	mode = "IsNotSet";
	steps = 0;
	strategys.clear();
	char* argv[] = { "prog", "stft", "stft", "backandforth", "fast" };
	Launcher L;
	int res = L.Launch(5, argv, mode, steps, strategys);
	EXPECT_EQ(strategys[0]->getName(), "STFT");
	EXPECT_EQ(strategys[1]->getName(), "STFT");
	EXPECT_EQ(strategys[2]->getName(), "BackAndForth");
	EXPECT_TRUE(L.GetSTFT1());
	EXPECT_TRUE(L.GetSouth2());
}

TEST(Strategys, STFTSouthampton) {
	SouthWinner::Reset();
	mode = "IsNotSet";
	steps = 0;
	strategys.clear();
	char* argv[] = { "prog", "stft", "southampton", "backandforth", "fast" };
	Launcher L;
	int res = L.Launch(5, argv, mode, steps, strategys);
	EXPECT_EQ(strategys[0]->getName(), "STFT");
	EXPECT_EQ(strategys[1]->getName(), "Southampton");
	EXPECT_EQ(strategys[2]->getName(), "BackAndForth");
	EXPECT_TRUE(L.GetSTFT1());
	EXPECT_TRUE(L.GetSouth2());
}

TEST(Strategys, SouthamptonSTFT) {
	SouthWinner::Reset();
	mode = "IsNotSet";
	steps = 0;
	strategys.clear();
	char* argv[] = { "prog", "southampton", "stft", "backandforth", "fast" };
	Launcher L;
	int res = L.Launch(5, argv, mode, steps, strategys);
	EXPECT_EQ(strategys[0]->getName(), "Southampton");
	EXPECT_EQ(strategys[1]->getName(), "STFT");
	EXPECT_EQ(strategys[2]->getName(), "BackAndForth");
	EXPECT_TRUE(L.GetSouth1());
	EXPECT_TRUE(L.GetSouth2());
}

TEST(Strategys, KindTraitorBackAndForth) {
	SouthWinner::Reset();
	mode = "IsNotSet";
	steps = 0;
	strategys.clear();
	char* argv[] = { "prog", "kind", "traitor", "backandforth", "fast" };
	Launcher L;
	int res = L.Launch(5, argv, mode, steps, strategys);
	EXPECT_EQ(strategys[0]->getName(), "Kind");
	EXPECT_EQ(strategys[1]->getName(), "Traitor");
	EXPECT_EQ(strategys[2]->getName(), "BackAndForth");
	EXPECT_TRUE(L.GetKind());
	EXPECT_TRUE(L.GetTraitor());
	EXPECT_TRUE(L.GetBack());
}

TEST(Strategys, TitForTatKind1) {
	SouthWinner::Reset();
	mode = "IsNotSet";
	steps = 0;
	strategys.clear();
	char* argv[] = { "prog", "titfortatkind", "kind", "backandforth", "fast" };
	Launcher L;
	int res = L.Launch(5, argv, mode, steps, strategys);
	EXPECT_EQ(strategys[0]->getName(), "TitForTatKind");
	EXPECT_EQ(strategys[1]->getName(), "Kind");
	EXPECT_EQ(strategys[2]->getName(), "BackAndForth");
	EXPECT_TRUE(L.GetTK());
}

TEST(Strategys, TitForTatKind2) {
	SouthWinner::Reset();
	mode = "IsNotSet";
	steps = 0;
	strategys.clear();
	char* argv[] = { "prog", "titfortatkind", "traitor", "backandforth", "fast" };
	Launcher L;
	int res = L.Launch(5, argv, mode, steps, strategys);
	EXPECT_EQ(strategys[0]->getName(), "TitForTatKind");
	EXPECT_EQ(strategys[1]->getName(), "Traitor");
	EXPECT_EQ(strategys[2]->getName(), "BackAndForth");
	EXPECT_TRUE(L.GetTK());
}

TEST(Strategys, TitForTatAnger1) {
	SouthWinner::Reset();
	mode = "IsNotSet";
	steps = 0;
	strategys.clear();
	char* argv[] = { "prog", "titfortatanger", "traitor", "backandforth", "fast" };
	Launcher L;
	int res = L.Launch(5, argv, mode, steps, strategys);
	EXPECT_EQ(strategys[0]->getName(), "TitForTatAnger");
	EXPECT_EQ(strategys[1]->getName(), "Traitor");
	EXPECT_EQ(strategys[2]->getName(), "BackAndForth");
	EXPECT_TRUE(L.GetTA());
}

TEST(Strategys, TitForTatAnger2) {
	SouthWinner::Reset();
	mode = "IsNotSet";
	steps = 0;
	strategys.clear();
	char* argv[] = { "prog", "titfortatanger", "kind", "backandforth", "fast" };
	Launcher L;
	int res = L.Launch(5, argv, mode, steps, strategys);
	EXPECT_EQ(strategys[0]->getName(), "TitForTatAnger");
	EXPECT_EQ(strategys[1]->getName(), "Kind");
	EXPECT_EQ(strategys[2]->getName(), "BackAndForth");
	EXPECT_TRUE(L.GetTA());
}
