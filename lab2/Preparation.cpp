#include "Preparation.h"

bool Preparation::IsDigit(std::string str) {
	for (auto iter = str.begin(); iter != str.end(); ++iter) {
		if (!isdigit(*iter)) {
			return false;
		}
	}
	return true;
}

bool Preparation::IsMode(char* str) {
	return !(strcmp(str, "detailed") && strcmp(str, "fast") && strcmp(str, "tournament"));
}

void Preparation::SetModeOptional(int size, std::string& mode) {
	if (size == 3) {
		mode = "detailed";
	}
	else {
		mode = "tournament";
	}
}

bool Preparation::SetOptions(int size, std::string& mode, int& steps, int i, int argc, char* argv[]) {
	if (size < 3) {
		return false;
	}
	if (i > argc - 1) {
		SetModeOptional(size, mode);
		steps = optionalSteps;
	}
	else {
		if (IsMode(argv[i])) {
			mode = argv[i];
			++i;
		}
		else {
			SetModeOptional(size, mode);
		}
		if (i > argc - 1) {
			steps = optionalSteps;
		}
		else {
			steps = atoi(argv[i]);
		}
	}
	return true;
}

Game* Preparation::Prepare(int& argc, char* argv[]) {
	int i = 1;
	int steps = 0;
	std::string mode = "IsNotSet";
	std::vector<Strategy*> strategys;
	for (; (i <= argc - 1) && !IsMode(argv[i]) && !IsDigit(argv[i]); ++i) {
		strategys.push_back(Factory<Strategy, std::string, Strategy* (*)()>::getInstance()->makeStrategy(argv[i]));
		if (!strategys[i - 1]) {
			return nullptr;
		}
	}

	if (!SetOptions(strategys.size(), mode, steps, i, argc, argv)) {
		return nullptr;
	}

	Game* G = Factory<Game, std::string, Game* (*)()>::getInstance()->makeStrategy(mode);
	if (G) {
		G->SetSteps(steps);
		G->SetStrategys(std::move(strategys));
	}
	return G;
}
