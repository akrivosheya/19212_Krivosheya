#include "Strategy.h"

class Kind : public Strategy {
public:
	void getRes(bool s1, bool s2) override;
	bool makeMove() override;
};

Strategy* createKind();
