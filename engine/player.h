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
    Sound engineSound{};
    float engineVolume = 1.0f;
    Sound stopSound{};
    Sound idleSound{};
    Sound turretRotateSound{};
    bool isMoving = false;
    bool wasMoving = false;
};
