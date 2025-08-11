#include "base.h"
#include "tank.h"
#include <raylib.h>


namespace Engine {
	// simple distance function
	static inline float Vec2Distance(const Vector2& a, const Vector2& b) {
		float dx = a.x - b.x;
		float dy = a.y - b.y;
		return sqrtf(dx * dx + dy * dy);
	};
	/* ----------------------------------  Base Tank   ---------------------------------- */
	BaseTank::BaseTank() {
		// load turret shout
		std::string soundPath = get_asset("tank-shot", AssetType::SOUND);
		tankFireSound = LoadSound(soundPath.c_str());
		loadFireAnimation();
	}

	BaseTank::~BaseTank() {
		UnloadTexture(texture);
		UnloadSound(tankFireSound);
		UnloadTexture(trackSystem.trackTexture);
	}

	void BaseTank::updateControl(float dt) {
		updateFireAnimation(dt);
		trackSystem.update(dt, position, rotation);
	}

	void BaseTank::spawn(float xPos, float yPos) {
		position = { xPos, yPos };
		trackSystem.prevPositionForTracks = position;
		trackSystem.totalDistanceTravelled = 0.0f;
	}
	/* ----------------------------------  Base Tank Texture loading   ---------------------------------- */
	void BaseTank::loadTexture(const std::string& tank_name) {
		name = tank_name;
		if (texture.id == 0) {
			texture = LoadTexture(get_asset(name).c_str());
			// Split the texture into body (left half) and turret (right half)
			int halfWidth = texture.width / 2;
			int height = texture.height;

			bodyRect = { 0, 0, (float)halfWidth, (float)height };
			turretRect = { (float)halfWidth, 0, (float)halfWidth, (float)height };
			trackSystem.loadTrackTexture("tank_track");
		}
	}

	/* ----------------------------------  Base Tank Fire animation loading  ---------------------------------- */
	void BaseTank::loadFireAnimation() {
		AnimationSeq fire_animation = get_animation_seq("tank_turret_fire");
		fireFrames = fire_animation.animations;
		fireFrameCount = fire_animation.frame_counts;
		fireTimer = 0.2f;
	}
	/* ----------------------------------  Base Tank Updating Fire animation   ---------------------------------- */
	void BaseTank::updateFireAnimation(float dt) {
		if (!isFiring || fireFrames.empty()) return;
		fireTimer += dt;
		if (fireTimer >= fireFrameTime) {
			fireTimer = 0.0f;
			currentFireFrame++;

			if (currentFireFrame >= fireFrameCount) {
				currentFireFrame = 0;
				isFiring = false;
			}
		}
	}


	/* ----------------------------------  Base Tank draw  ---------------------------------- */
	void BaseTank::draw() {
		// for debug animation
		//DrawText(TextFormat("Firing frame: %d/%d", currentFireFrame, fireFrameCount), 10, 10, 20, RED);
		//DrawText(TextFormat("Firing: %d/%d", isFiring, fireFrameCount), 30, 30, 20, RED);
		trackSystem.draw();
		/* ----------------------------------  Tank Body and Turret Drawing  ---------------------------------- */
		DrawTexturePro(
			texture,
			bodyRect,
			{ position.x, position.y, bodyRect.width, bodyRect.height },
			{ bodyRect.width / 2, bodyRect.height / 2 }, // rotate around center
			rotation,
			WHITE
		);
		DrawTexturePro(
			texture,
			turretRect,
			{ position.x, position.y, turretRect.width, turretRect.height },
			{ turretRect.width / 2, turretRect.height / 2 },
			turretRotation,
			WHITE
		);
		
		

		/* ----------------------------------  Turret Shot Animation  ---------------------------------- */
		if (isFiring && currentFireFrame < fireFrameCount) {
			Texture2D& fireTex = fireFrames[currentFireFrame];
			// Calculate position in front of turret, considering turret rotation
			Vector2 firePos = position;
			// Calculate offset vector rotated by turretRotation degrees
			float rad = DEG2RAD * turretRotation;
			Vector2 rotatedOffset = {
				fireOffset.x * cosf(rad) - fireOffset.y * sinf(rad),
				fireOffset.x * sinf(rad) + fireOffset.y * cosf(rad)
			};
			firePos.x += rotatedOffset.x;
			firePos.y += rotatedOffset.y;
			// Draw fire centered on firePos with turretRotation rotation around its center
			Rectangle sourceRec = { 0, 0, (float)fireTex.width, (float)fireTex.height };
			Rectangle destRec = { firePos.x, firePos.y, (float)fireTex.width, (float)fireTex.height };
			Vector2 origin = { fireTex.width / 2.0f, fireTex.height + 150.0f };
			DrawTexturePro(fireTex, sourceRec, destRec, origin, turretRotation + 180.0f, WHITE);
		}
		/* ----------------------------------  Tank Range Indicator  ---------------------------------- */
		Color rangeColor = Color{ 255, 0, 0, 50 }; // Red, transparent
		DrawCircleLines((int)position.x, (int)position.y, (float)range, rangeColor);

		// Calculate range dot using turret logic
		float rad = DEG2RAD * turretRotation;
		Vector2 rangeOffset = {
			0.0f * cosf(rad) - (range)*sinf(rad),  // X offset
			0.0f * sinf(rad) + (range)*cosf(rad)   // Y offset
		};

		// Position of the dot at max range
		Vector2 rangeDot = {
			position.x + rangeOffset.x,
			position.y + rangeOffset.y
		};
		// set turret target position so later we know where to BOOM!
		turret_target_position = rangeDot;

		DrawCircleV(rangeDot, 4.0f, RED);
	}


	/* ----------------------------------  LightTank  ---------------------------------- */
	LightTank::LightTank() {
		name = "Light Tank";
		tank_class = TankClass::LIGHT;
		ammo_type = AmmoType::ANTI_TANK;
		tank_role = TankRole::DESTROYER;
		current_ammo = 15;
		health = 60;
		movement_speed = 160;
		damage = 10;
		range = 800;
		defence = 10;
		reload_time = 3;
		level = 1;
	}

	void LightTank::updateControl(float dt) {
		BaseTank::updateControl(dt);
	}
	void LightTank::attack() {
		if (!isFiring) {
			isFiring = true;
			currentFireFrame = 0;
			fireTimer = 0.0f; // start counting fresh
			PlaySound(tankFireSound); // plays only once per shot
		}
	}

	/* ----------------------------------  Meduim Tank  ---------------------------------- */
	MediumTank::MediumTank() {
		name = "Medium Tank";
		tank_class = TankClass::MEDIUM;
		ammo_type = AmmoType::EXPLOSIVE;
		tank_role = TankRole::FIGHTER;

		current_ammo = 10;
		health = 80;
		movement_speed = 8;
		damage = 21;
		range = 220;
		defence = 20;
		reload_time = 4;
		level = 1;
	}
	void MediumTank::updateControl(float dt) {
		BaseTank::updateControl(dt);
	}
	void MediumTank::attack() {
		if (!isFiring) {
			isFiring = true;
			currentFireFrame = 0;
			fireTimer = 0.0f;
			// Play firing sound later
		}
	}


	/* ----------------------------------  Heavy Tank  ---------------------------------- */
	HeavyTank::HeavyTank() {
		name = "Heavy Tank";
		tank_class = TankClass::HEAVY;
		ammo_type = AmmoType::INCENDIARY;
		tank_role = TankRole::FIGHTER;
		current_ammo = 8;
		health = 120;
		movement_speed = 4;
		damage = 32;
		range = 250;
		defence = 35;
		reload_time = 5;
		level = 1;
	}
	void HeavyTank::updateControl(float dt) {
		BaseTank::updateControl(dt);
	}
	void HeavyTank::attack() {
		if (!isFiring) {
			isFiring = true;
			currentFireFrame = 0;
			fireTimer = 0.0f;
			// Play firing sound later
		}
	}
}