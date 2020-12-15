#include "Strategy.h"

class BackAndForth : public Strategy {
public:
	virtual ~BackAndForth() = default;
	void putDecisions(bool decision1, bool decision2) override;
	bool makeDecision() override;
	std::string getName() override;
	void reload() override;
private:
	bool cORd = help;
	std::string name = "BackAndForth";
};

Strategy* createBackAndForth();
