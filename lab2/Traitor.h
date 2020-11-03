#include "Strategy.h"

class Traitor : public Strategy {
public:
	void getRes(bool s1, bool s2) override;
	bool makeMove() override;
	std::string getName() override;
	void reload() override {};
private:
	std::string name = "Traitor";
};

Strategy* createTraitor();
