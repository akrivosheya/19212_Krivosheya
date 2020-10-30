#include "Strategy.h"

class Southampton : public Strategy {
public:
	Southampton();/* : counter(0), winner(true), s1(true), s2(true) {
		if (winnerIs) {
			winner = false;
			return;
		}
		winnerIs = true;
	}*/
	void getRes(bool s1, bool s2) override;
	bool makeMove() override;
private:
	static constexpr int dancing = 618;
	static constexpr int mask = 1;
	static bool winnerIs;
	int counter;
	bool winner;
	bool s1;
	bool s2;
};

//bool Southampton::winnerIs = false;

Strategy* createSouthampton();
