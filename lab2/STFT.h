#include "Strategy.h"
#include "SouthWinner.h"

class STFT : public Strategy, public SouthWinner {
public:
	STFT();
	void getRes(bool s1, bool s2) override;
	bool makeMove() override;
	std::string getName() override;
	void reload() override;
private:
	static constexpr int dancing = 618;
	static constexpr int mask = 1;
	std::string name = "STFT";
	bool betrayed;
	int counter;
	bool winner;
	bool s1;
	bool s2;
};

Strategy* createSTFT();
