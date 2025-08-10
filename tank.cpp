#include "base.h"
#include "tank.h"
#include <raylib.h>

// BaseTank destructor
//BaseTank::BaseTank() {};
//
BaseTank::~BaseTank() {
    UnloadTexture(texture);
}

void BaseTank::spawn(float xPos, float yPos) {
    position = { xPos, yPos };
    DrawTexture(texture, position.x, position.y, WHITE);
}

void BaseTank::loadTexture(const std::string& tank_name) {
    name = tank_name;
    if (texture.id == 0) {
        texture = LoadTexture(get_asset(name).c_str());
        // Split the texture into body (left half) and turret (right half)
        int halfWidth = texture.width / 2;
        int height = texture.height;

        bodyRect = { 0, 0, (float)halfWidth, (float)height };
        turretRect = { (float)halfWidth, 0, (float)halfWidth, (float)height };
    }
    }

void BaseTank::draw() {
    // Draw tank body
    DrawTexturePro(
        texture,
        bodyRect,
        { position.x, position.y, bodyRect.width, bodyRect.height },
        { bodyRect.width / 2, bodyRect.height / 2 }, // rotate around center
        rotation,
        WHITE
    );

    // Turret rotation toward mouse
    Vector2 mousePos = GetMousePosition();
    float turretRotation = atan2(mousePos.y - position.y, mousePos.x - position.x) * RAD2DEG;

    DrawTexturePro(
        texture,
        turretRect,
        { position.x, position.y, turretRect.width, turretRect.height },
        { turretRect.width / 2, turretRect.height / 2 },
        turretRotation,
        WHITE
    );
}


void BaseTank::movement() {
    float dt = GetFrameTime();

    if (IsKeyDown(KEY_RIGHT)) rotation += rotation_speed * dt;
    if (IsKeyDown(KEY_LEFT))  rotation -= rotation_speed * dt;

    if (IsKeyDown(KEY_UP)) {
        position.x -= sinf(DEG2RAD * rotation) * movement_speed * dt;
        position.y += cosf(DEG2RAD * rotation) * movement_speed * dt;
    }
    if (IsKeyDown(KEY_DOWN)) {
        position.x += sinf(DEG2RAD * rotation) * movement_speed * dt;
        position.y -= cosf(DEG2RAD * rotation) * movement_speed * dt;
    }

    // Turret rotation with mouse
    Vector2 mouse = GetMousePosition();
    turretRotation = atan2f(mouse.y - position.y, mouse.x - position.x) * RAD2DEG;
}

// -------- LightTank --------
LightTank::LightTank() {
    name = "Light Tank";
    tank_class = TankClass::LIGHT;
    ammo_type = AmmoType::ANTI_TANK;
    tank_role = TankRole::DESTROYER;

    current_ammo = 15;
    health = 60;
    movement_speed = 30;
    damage = 10;
    range = 15;
    defence = 10;
    reload_time = 3;
    level = 1;
}

void LightTank::attack() {
    // Implement LightTank specific attack behavior here
}



// -------- MediumTank --------
MediumTank::MediumTank() {
    name = "Medium Tank";
    tank_class = TankClass::MEDIUM;
    ammo_type = AmmoType::EXPLOSIVE;
    tank_role = TankRole::FIGHTER;

    current_ammo = 10;
    health = 80;
    movement_speed = 8;
    damage = 21;
    range = 18;
    defence = 20;
    reload_time = 4;
    level = 1;
}

void MediumTank::attack() {
    // Implement MediumTank specific attack behavior here
}


// -------- HeavyTank --------
HeavyTank::HeavyTank() {
    name = "Heavy Tank";
    tank_class = TankClass::HEAVY;
    ammo_type = AmmoType::INCENDIARY;
    tank_role = TankRole::FIGHTER;

    current_ammo = 8;
    health = 120;
    movement_speed = 4;
    damage = 32;
    range = 25;
    defence = 35;
    reload_time = 5;
    level = 1;
}

void HeavyTank::attack() {
    // Implement HeavyTank specific attack behavior here
}

