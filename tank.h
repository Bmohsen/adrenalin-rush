#pragma once

#include <string>
#include "raylib.h"  // For Vector2, Texture2D, LoadTexture, etc.

enum class TankClass {
    LIGHT,
    MEDIUM,
    HEAVY,
};

enum class AmmoType {
    ANTI_TANK,
    EXPLOSIVE,
    INCENDIARY,
};

enum class TankRole {
    FIGHTER,
    DESTROYER,
};

struct Tank {
    std::string name;
    std::string base_img;
};

// Base class for tanks
class BaseTank {
public:
    BaseTank() = default;
    virtual ~BaseTank();

    void spawn(float xPos, float yPos);
    void loadTexture(const std::string& tank_name = "m6");
    void draw();
    virtual void attack() = 0;
    void movement();

    std::string name;
    TankClass tank_class = TankClass::LIGHT;
    AmmoType ammo_type = AmmoType::EXPLOSIVE;
    TankRole tank_role = TankRole::FIGHTER;

    int current_ammo = 5;
    int health = 100;
    float movement_speed = 100.0f; // pixels/sec
    float rotation = 0.0f;         // body rotation
    float turretRotation = 0.0f;   // turret rotation
    float rotation_speed = 90.0f;  // degrees/sec
    int damage = 12;
    int range = 12;
    int defence = 15;
    int reload_time = 3;
    int level = 1;
    int kills = 0;

    Vector2 position{ 0, 0 };
    Texture2D texture{};
    Rectangle bodyRect{};
    Rectangle turretRect{};
};

// Derived tank classes
class LightTank : public BaseTank {
public:
    LightTank();
    void attack() override;
};

class MediumTank : public BaseTank {
public:
    MediumTank();
    void attack() override;
};

class HeavyTank : public BaseTank {
public:
    HeavyTank();
    void attack() override;
};
