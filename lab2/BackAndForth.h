#include "Strategy.h"

class BackAndForth : public Strategy {
public:
	void getRes(bool s1, bool s2) override;
	bool makeMove() override;
private:
	bool cORd = c;
};

Strategy* createBackAndForth();
