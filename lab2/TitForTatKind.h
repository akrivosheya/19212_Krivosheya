#include "Strategy.h"

class TitForTatKind : public Strategy {
public:
	void getRes(bool s1, bool s2) override;
	bool makeMove() override;
private:
	bool betrayed = false;
};

Strategy* createTitForTatKind();
