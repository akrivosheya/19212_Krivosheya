#include "Printer.h"

void Printer::PrintRes(Strategy* S1, Strategy* S2, Strategy* S3, 
	int pointS1, int pointS2, int pointS3) {
	std::cout << S1->getName() << " - " << pointS1 << "; "
		<< S2->getName() << " - " << pointS2 <<
		"; " << S3->getName() << " - " << pointS3 << std::endl;
}

void Printer::PrintTournamentRes(std::vector<Strategy*>& strategys, std::vector<int>& victories) {
	std::cout << std::endl << "Results:" << std::endl;
	for (int i = 0; i < strategys.size(); ++i) {
		std::cout << i << ") " << strategys[i]->getName() << " - " << victories[i] << std::endl;
	}
}

void Printer::PrintDetailedRes(bool moveS1, bool moveS2, bool moveS3,
	int pointS1, int pointS2, int pointS3,
	int getS1, int getS2, int getS3) {
	std::cout << ((moveS1) ? "C" : "D") << " " << ((moveS2) ? "C" : "D") << " " << ((moveS3) ? "C" : "D")
		<< "  =>  " << getS1 << " " << getS2 << " " << getS3
		<< "  =>  " << pointS1 << " " << pointS2 << " " << pointS3 << std::endl;
}
