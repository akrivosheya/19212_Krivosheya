#include "Game.h"
#include "Preparation.h"

int main(int argc, char* argv[]) {
	if (argc < 4) return -1;
	int steps = 0;
	std::string mode = "IsNotSet";
	std::vector<Strategy*> strategys;
	Preparation P;
	Game* G = P.Prepare(steps, mode, strategys, argc, argv);
	if (!G) {
		return -1;
	}
	G->Play(steps, strategys, "Matrix.txt");
	delete G;
	return 0;

}
