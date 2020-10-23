#include <memory>
#include <unordered_map>
#include "Strategy.h"
#include "Factory.h"
#include "BackAndForth.h"
#include "Kind.h"
#include "Traitor.h"
#include "Southampton.h"
#include "TitForTatAnger.h"
#include "TitForTatKind.h"

int main(int argc, char* argv[]) {
	if (argc < 2) return -1;

	FILE* matrix = fopen("Matrix.txt", "w");
	fprintf(matrix, "s1 s2 s3      s1 s2 s3\n");

	int i = 1;
	std::unordered_map<int, Strategy*>  strategys;
	for (; argv[i] != "detailed" && argv[i] != "fast" && argv[i] != "tournament"; ++i) {
		strategys.insert({ i, Factory<Strategy, std::string, Strategy* (*)()>::getInstance()->makeStrategy(argv[i]) });
	}

	if (argv[i] == "fast") {
		int steps = atoi(argv[i + 1]);
		bool moveS1, moveS2, moveS3;
		int pointS1, pointS2, pointS3;
		if
		for (int j = 0; j < steps; ++j) {
			moveS1 = (strategys.find(1)->second)->makeMove();
			moveS2 = (strategys.find(2)->second)->makeMove();
			moveS3 = (strategys.find(3)->second)->makeMove();
			(strategys.find(1)->second)->getRes(moveS2, moveS3);
			(strategys.find(2)->second)->getRes(moveS1, moveS3);
			(strategys.find(3)->second)->getRes(moveS1, moveS2);
			fprintf(matrix, " %c  %c  %c  =>  %d  %d  %d\n", (moveS1) ? 'C' : 'D', (moveS1) ? 'C' : 'D', (moveS1) ? 'C' : 'D', 
				)
		}
	}

	std::unique_ptr<Strategy> u(Factory<Strategy, std::string, Strategy* (*)()>::getInstance()->makeStrategy(argv[1]));//смарт поинтер
}
