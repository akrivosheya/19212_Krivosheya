#include "Printer.h"

void Printer::PrintRes(std::vector<Strategy*>& strategys,
	std::vector<int> points, int i, int j, int k) {
	std::cout << strategys[i]->getName() << " - " << points[0] << "; "
		<< strategys[j]->getName() << " - " << points[1] <<
		"; " << strategys[k]->getName() << " - " << points[2] << std::endl;
}

void Printer::PrintTournamentRes(std::vector<Strategy*>& strategys, 
	std::vector<int>& victories) {
	std::cout << std::endl << "Results:" << std::endl;
	for (int i = 0; i < strategys.size(); ++i) {
		std::cout << i << ") " << strategys[i]->getName() << " - " << victories[i] << std::endl;
	}
}

void Printer::PrintDetailedRes(std::vector<bool> decisions, 
	std::vector<int> gets, std::vector<int> points) {
	std::cout << ((decisions[0]) ? "C" : "D") << " " 
		<< ((decisions[1]) ? "C" : "D") << " " << ((decisions[2]) ? "C" : "D")
		<< "  =>  " << gets[0] << " " << gets[1] << " " << gets[2]
		<< "  =>  " << points[0] << " " << points[1] << " " << points[2] << std::endl;
}
