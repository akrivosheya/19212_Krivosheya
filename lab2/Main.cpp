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

	FILE* matrix;
	fopen_s(&matrix, "Matrix.txt", "w");
	fprintf(matrix, "s1 s2 s3      s1 s2 s3\n");

	int i = 1;
	std::unordered_map<int, Strategy*>  strategys;
	for (; i < argc && argv[i] != "detailed" && argv[i] != "fast" && argv[i] != "tournament"; ++i) {
		std::cout << (argv[i] == "fast") << std::endl;
		if (argv[i] == "fast") break;
		strategys.insert({ i, Factory<Strategy, std::string, Strategy* (*)()>::getInstance()->makeStrategy(argv[i]) });
	}

	if (argv[i] == "fast") {
		int steps = atoi(argv[i + 1]);
		bool moveS1, moveS2, moveS3;
		int pointS1 = 0, pointS2 = 0, pointS3 = 0;
		for (int j = 0; j < steps; ++j) {
			moveS1 = (strategys.find(1)->second)->makeMove();
			moveS2 = (strategys.find(2)->second)->makeMove();
			moveS3 = (strategys.find(3)->second)->makeMove();
			pointS1 += (moveS1) ? ((moveS2 && moveS3) ? 7 : ((moveS2 || moveS3) ? 3 : 0)) : ((moveS2 && moveS3) ? 9 : ((moveS2 || moveS3) ? 5 : 1));
			pointS2 += (moveS2) ? ((moveS1 && moveS3) ? 7 : ((moveS1 || moveS3) ? 3 : 0)) : ((moveS1 && moveS3) ? 9 : ((moveS1 || moveS3) ? 5 : 1));
			pointS3 += (moveS3) ? ((moveS2 && moveS1) ? 7 : ((moveS2 || moveS1) ? 3 : 0)) : ((moveS2 && moveS1) ? 9 : ((moveS2 || moveS1) ? 5 : 1));
			(strategys.find(1)->second)->getRes(moveS2, moveS3);
			(strategys.find(2)->second)->getRes(moveS1, moveS3);
			(strategys.find(3)->second)->getRes(moveS1, moveS2);
			fprintf(matrix, " %c  %c  %c  =>  %d  %d  %d\n", (moveS1) ? 'C' : 'D', (moveS1) ? 'C' : 'D', (moveS1) ? 'C' : 'D',
				pointS1, pointS2, pointS3);
		}
		std::cout << "s1 - " << pointS1 << ";s2 - " << pointS2 << ";s3 - " << pointS3 << std::endl;
		std::cin >> i;
	}

	std::unique_ptr<Strategy> u(Factory<Strategy, std::string, Strategy* (*)()>::getInstance()->makeStrategy(argv[1]));//смарт поинтер
}
