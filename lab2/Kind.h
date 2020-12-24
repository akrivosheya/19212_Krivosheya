#include "Strategy.h"

class Kind : public Strategy {
public:
	void putDecisions(bool decision1, bool decision2) override;
	bool makeDecision() override;
	std::string getName() override;
	void reload() override {};
private:
	std::string name = "Kind";
};

Strategy* createKind() {
	return new Kind;
}
