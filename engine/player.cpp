// player.cpp
#include "player.h"
#include "raylib.h"
#include <cmath>

Player::Player(BaseTank* tank) : controlledTank(tank) {
    // Player "possesses" the tank instance
}

Player::~Player() {
    if (controlledTank) {
        delete controlledTank;  // clean up the tank
    }
}

void Player::updateControl(float dt) {
    handleMovement(dt);
}

void Player::draw() {
    if (controlledTank) {
        controlledTank->draw();
    }
}

void Player::handleMovement(float dt) {
    if (!controlledTank) return;

    if (IsKeyDown(KEY_RIGHT)) controlledTank->rotation += controlledTank->rotation_speed * dt;
    if (IsKeyDown(KEY_LEFT))  controlledTank->rotation -= controlledTank->rotation_speed * dt;

    if (IsKeyDown(KEY_UP)) {
        controlledTank->position.x += sinf(DEG2RAD * controlledTank->rotation) * controlledTank->movement_speed * dt;
        controlledTank->position.y -= cosf(DEG2RAD * controlledTank->rotation) * controlledTank->movement_speed * dt;
    }
    if (IsKeyDown(KEY_DOWN)) {
        controlledTank->position.x -= sinf(DEG2RAD * controlledTank->rotation) * controlledTank->movement_speed * dt;
        controlledTank->position.y += cosf(DEG2RAD * controlledTank->rotation) * controlledTank->movement_speed * dt;
    }

    if (IsKeyDown(KEY_Q)) {
        controlledTank->turretRotation -= controlledTank->rotation_speed * dt;
    }
    if (IsKeyDown(KEY_E)) {
        controlledTank->turretRotation += controlledTank->rotation_speed * dt;
    }

    // Clamp turretRotation
    if (controlledTank->turretRotation < 0) controlledTank->turretRotation += 360;
    if (controlledTank->turretRotation >= 360) controlledTank->turretRotation -= 360;

    // Clamp body rotation
    if (controlledTank->rotation < 0) controlledTank->rotation += 360;
    if (controlledTank->rotation >= 360) controlledTank->rotation -= 360;
}
