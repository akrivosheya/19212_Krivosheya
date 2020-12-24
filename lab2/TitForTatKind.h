#include "Strategy.h"

class TitForTatKind : public Strategy {
public:
	void putDecisions(bool decision1, bool decision2) override;
	bool makeDecision() override;
	std::string getName() override;
	void reload() override;
private:
	bool betrayed = false;
	std::string name = "TitForTatKind";
};

Strategy* createTitForTatKind() {
	return new TitForTatKind;
}
