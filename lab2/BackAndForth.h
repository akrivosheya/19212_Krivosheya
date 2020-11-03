#include "Strategy.h"

class BackAndForth : public Strategy {
public:
	void getRes(bool s1, bool s2) override;
	bool makeMove() override;
	std::string getName() override;
	void reload() override;
private:
	bool cORd = c;
	std::string name = "BackAndForth";
};

Strategy* createBackAndForth();
