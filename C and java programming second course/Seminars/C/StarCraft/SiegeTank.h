#include "Unit.h"

class SiegeTank : public Unit {
public:
    void move(int x, int y) override;
};

SiegeTank* createSiegeTank();
