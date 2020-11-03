#pragma once
#include <iostream>

class Strategy {
public:
	virtual ~Strategy() {}
	virtual void getRes(bool s1, bool s2) = 0;
	virtual bool makeMove() = 0;
	virtual std::string getName() = 0;
	virtual void reload() = 0;
protected:
	static constexpr bool c = true;
	static constexpr bool d = false;
};
