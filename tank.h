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

    // Spawn the tank at given position with a name (default: "t34")
    void spawn(float xPos, float yPos);
    void loadTexture(const std::string& tank_name = "t34");
    // Virtual functions for specific behavior
    virtual void attack() = 0;
    virtual void movement() = 0;

    // Getters (optional, could add setters if needed)
    const std::string& getName() const { return name; }
    TankClass getTankClass() const { return tank_class; }
    AmmoType getAmmoType() const { return ammo_type; }
    TankRole getTankRole() const { return tank_role; }
    std::string name;
    TankClass tank_class = TankClass::LIGHT;
    AmmoType ammo_type = AmmoType::EXPLOSIVE;
    TankRole tank_role = TankRole::FIGHTER;

    int current_ammo = 5;
    int health = 100;
    int movement_speed = 10;
    int damage = 12;
    int range = 12;
    int defence = 15;
    int reload_time = 3; // seconds
    int level = 1;
    int kills = 0;

    Vector2 position{ 0, 0 };
    Texture2D texture{};
};

// Derived tank classes
class LightTank : public BaseTank {
public:
    LightTank();
    void attack() override;
    void movement() override;
};

class MediumTank : public BaseTank {
public:
    MediumTank();
    void attack() override;
    void movement() override;
};

class HeavyTank : public BaseTank {
public:
    HeavyTank();
    void attack() override;
    void movement() override;
};
