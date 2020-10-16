#include "Strategy.h"

class Traitor : public Strategy {
public:
	void getRes(bool s1, bool s2) override;
	bool makeMove() override;
};

Strategy* createTraitor();
