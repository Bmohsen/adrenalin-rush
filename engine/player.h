#pragma once
#include "tank.h"

class Player 
{
public:
    Player(BaseTank* tank);
    ~Player();
    void updateControl(float dt);
    void draw();

private:
    BaseTank* controlledTank;
    void handleMovement(float dt);
};
