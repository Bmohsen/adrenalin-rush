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
    }
}

// -------- LightTank --------
LightTank::LightTank() {
    name = "Light Tank";
    tank_class = TankClass::LIGHT;
    ammo_type = AmmoType::ANTI_TANK;
    tank_role = TankRole::DESTROYER;

    current_ammo = 15;
    health = 60;
    movement_speed = 12;
    damage = 10;
    range = 15;
    defence = 10;
    reload_time = 3;
    level = 1;
}

void LightTank::attack() {
    // Implement LightTank specific attack behavior here
}

void LightTank::movement() {
    // Implement LightTank specific movement behavior here
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

void MediumTank::movement() {
    // Implement MediumTank specific movement behavior here
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

void HeavyTank::movement() {
    // Implement HeavyTank specific movement behavior here
}
