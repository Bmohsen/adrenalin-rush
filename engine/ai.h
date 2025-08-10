#pragma once
#include "tank.h"

class AITank : public BaseTank {
public:
    AITank();

    void updateControl(float dt) override;
    void attack() override;

private:
    void runAI(float dt);
};
