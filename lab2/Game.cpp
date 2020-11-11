#include "Game.h"

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

void SetModeOptional(const int& size, std::string& mode) {
	if (size == 3) {
		mode = "detailed";
	}
	else {
		mode = "tournament";
	}
}

bool SetOptions(const int& size, std::string& mode, int& steps, int& i, const int& argc, char* argv[]) {
	if (size < 3) {
		return false;
	}
	if (i > argc - 1) {
		SetModeOptional(size, mode);
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
			SetModeOptional(size, mode);
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
