#include "Strategy.h"
#include "BackAndForth.h"

class SouthBack : public BackAndForth {
public:
	SouthBack();
	void putDecisions(bool decision1, bool decision2) override;
	bool makeDecision() override;
	std::string getName() override;
	void reload() override;
private:
	static constexpr int dancing = 618;
	static constexpr int mask = 1;
	std::string name = "SouthBack";
	int counter;
	bool winner;
	bool winnerIs;
	bool friendIs;
	bool master1;
	bool master2;
	bool lastDecision;
};

Strategy* createSouthBack();
