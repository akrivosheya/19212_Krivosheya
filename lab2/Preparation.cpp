#include "Preparation.h"

bool Preparation::IsDigit(std::string str) {
	for (int i = 0; i < str.size(); ++i) {
		if (!isdigit(str[i])) {
			return false;
		}
	}
	return true;
}

bool Preparation::IsMode(char* str) {
	return !(strcmp(str, "detailed") && strcmp(str, "fast") && strcmp(str, "tournament"));
}

void Preparation::SetModeOptional(const int& size, std::string& mode) {
	if (size == 3) {
		mode = "detailed";
	}
	else {
		mode = "tournament";
	}
}

bool Preparation::SetOptions(const int& size, std::string& mode, int& steps, int& i, const int& argc, char* argv[]) {
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
			if (i > argc - 1) {
				steps = optionalSteps;
			}
			else {
				steps = atoi(argv[i]);
			}
		}
		else {
			SetModeOptional(size, mode);
			if (i > argc - 1) {
				steps = optionalSteps;
			}
			else {
				steps = atoi(argv[i]);
			}
		}
	}
	return true;
}

Game* Preparation::Prepare(int& steps, std::string& mode, std::vector<Strategy*>& strategys, int& argc, char* argv[]) {
	int i = 1;
	steps = 0;
	mode = "IsNotSet";
	for (; (i <= argc - 1) && !IsMode(argv[i]) && !IsDigit(argv[i]); ++i) {
		strategys.push_back(Factory<Strategy, std::string, Strategy* (*)()>::getInstance()->makeStrategy(argv[i]));
		if (!strategys[i - 1]) {
			return nullptr;
		}
	}

	if (!SetOptions(strategys.size(), mode, steps, i, argc, argv)) {
		return nullptr;
	}

	return Factory<Game, std::string, Game* (*)()>::getInstance()->makeStrategy(mode);
}
