#include "Strategy.h"

class Kind : public Strategy {
public:
	void getRes(int s1, int s2) override;
	bool makeMove() override;
};

Kind* createKind();
