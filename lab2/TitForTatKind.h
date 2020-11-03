#include "Strategy.h"

class TitForTatKind : public Strategy {
public:
	void getRes(bool s1, bool s2) override;
	bool makeMove() override;
	std::string getName() override;
	void reload() override;
private:
	bool betrayed = false;
	std::string name = "TitForTatKind";
};

Strategy* createTitForTatKind();
