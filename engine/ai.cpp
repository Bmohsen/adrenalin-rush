#include "ai.h"
#include <cmath>   // for atan2f, fabs
#include "raylib.h"

// we need a way to get the player position for AI targeting
// For now, declare an external/global function or variable to get it
extern Vector2 getPlayerPosition();

AITank::AITank() {
    // Initialize AI tank defaults if needed
}

void AITank::updateControl(float dt) {
    runAI(dt);
}

void AITank::attack() {
    // Implement AI tank attack logic here
}

void AITank::runAI(float dt) {
    Vector2 playerPos = getPlayerPosition();  // get player position from game state

    // Calculate desired turret rotation to face the player
    float desiredTurretRotation = atan2f(playerPos.y - position.y, playerPos.x - position.x) * RAD2DEG;

    // Calculate shortest rotation difference
    float rotationDifference = desiredTurretRotation - turretRotation;
    if (rotationDifference > 180) rotationDifference -= 360;
    if (rotationDifference < -180) rotationDifference += 360;

    float rotationStep = rotation_speed * dt;

    // Smoothly rotate turret toward player
    if (fabs(rotationDifference) < rotationStep) {
        turretRotation = desiredTurretRotation;
    }
    else if (rotationDifference > 0) {
        turretRotation += rotationStep;
    }
    else {
        turretRotation -= rotationStep;
    }

    // Clamp turretRotation between 0 and 360
    if (turretRotation < 0) turretRotation += 360;
    if (turretRotation >= 360) turretRotation -= 360;

    // TODO: Add body rotation, movement, firing logic
}
