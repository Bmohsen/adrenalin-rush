#pragma once

#include <string>
#include "base.h" 
#include "tank_tire_system.h"
#include <vector>

namespace Engine {

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


	/* ----------------------------------  Base Tank defination  ---------------------------------- */
	class BaseTank {
	public:
		BaseTank();
		virtual ~BaseTank();
		virtual void updateControl(float dt);
		virtual void attack() = 0;
		void spawn(float xPos, float yPos);
		void loadTexture(const std::string& tank_name = "m6");
		// optional, in future different tank classes (light, meduim and heavy) may have different animation
		virtual void loadFireAnimation();
		void updateFireAnimation(float dt);
		void draw();

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
		float movement_speed = 100.0f;
		float rotation = 180.0f;
		float turretRotation = 180.0f;
		float rotation_speed = 90.0f;
		int damage = 12;
		int range = 400;
		int defence = 15;
		int reload_time = 3;
		int level = 1;
		int kills = 0;

		TankTireSystem trackSystem;
		Vector2 position{ 0, 0 };
		Vector2 turret_target_position{ 0, 0 };
		Texture2D texture{};
		Rectangle bodyRect{};
		Rectangle turretRect{};
		std::vector<Texture2D> fireFrames;
		Vector2 fireOffset{ 0, -30 };
		int fireFrameCount = 0;
		float fireFrameTime = 0.0f;  // 50ms per frame (20 FPS animation)
		float fireTimer = 0.0f;       // start at 0 so it counts up
		int currentFireFrame = 0;
		bool isFiring = false;
		Sound tankFireSound{};

	};

	// Derived tank classes
	class LightTank : public BaseTank {
	public:
		LightTank();
		void updateControl(float dt) override; // optional
		void attack() override;
	};

	class MediumTank : public BaseTank {
	public:
		MediumTank();
		void updateControl(float dt) override; // optional
		void attack() override;
	};

	class HeavyTank : public BaseTank {
	public:
		HeavyTank();
		void updateControl(float dt) override; // optional
		void attack() override;
	};
}