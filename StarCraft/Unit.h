#pragma once
#include <iostream>

class Unit {
public:
    virtual void move(int x, int y) = 0;
    virtual ~Unit(){}
};
