#pragma once
#include <iostream>

class Strategy {
public:
	virtual ~Strategy() {}
	virtual void getRes(int s1, int s2) = 0;
	virtual bool makeMove() = 0;
};
