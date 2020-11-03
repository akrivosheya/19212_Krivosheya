#include "Strategy.h"

class Southampton : public Strategy {
public:
	Southampton();
	void getRes(bool s1, bool s2) override;
	bool makeMove() override;
	std::string getName() override;
	void reload() override;
private:
	static constexpr int dancing = 618;
	static constexpr int mask = 1;
	static bool winnerIs;
	std::string name = "Southampton";
	int counter;
	bool winner;
	bool s1;
	bool s2;
};

Strategy* createSouthampton();
