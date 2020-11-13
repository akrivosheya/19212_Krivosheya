#include <fstream>
#include <vector>
#include "Game.h"
#include "Factory.h"

int main(int argc, char* argv[]) {
	if (argc < 4) return -1;

	std::ofstream matrix("Matrix.txt");
	matrix << "s1 s2 s3" << std::endl;

	int i = 1, steps = 0;
	std::string mode = "IsNotSet";
	std::vector<Strategy*> strategys;
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
	int pointS1 = 0, pointS2 = 0, pointS3 = 0, getS1, getS2, getS3;

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
				<< "  =>  " << pointS1 << " " << pointS2 << " " << pointS3 <<  std::endl;
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
