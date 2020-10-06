#include "Unit.h"

class Zergling : public Unit {
public:
    void move(int x, int y) override;
};

Zergling* createZergling();
