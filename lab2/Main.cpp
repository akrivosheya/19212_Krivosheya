#include "Game.h"
#include "Preparation.h"

int main(int argc, char* argv[]) {
	if (argc < 4) return -1;
	Preparation P;
	std::unique_ptr<Game> G(P.Prepare(argc, argv));
	if (!G) {
		return -1;
	}
	Printer Print;
	std::ifstream file;
	file.open("Matrix.txt");
	G->SetRules(file);
	G->Play(Print);
	return 0;
}
