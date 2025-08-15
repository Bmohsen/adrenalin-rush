// player.cpp
#include "base.hpp"
#include "player.hpp"
#include "raylib.h"
#include <cmath>

namespace Engine
{
	namespace Player
	{
		/* ----------------------------------  Player Class  ---------------------------------- */
		Player::Player(BaseTank *tank) : controlledTank(tank)
		{
			init_tank();
			init_player_settings();
		}
		Player::~Player()
		{
			if (controlledTank)
			{
				delete controlledTank; // clean up the tank
			}
			// Unload sounds if loaded
			UnloadSound(engineSound);
			UnloadSound(stopSound);
			UnloadSound(idleSound);
			UnloadSound(turretRotateSound);
		}

		/* ----------------------------------  Player Tank init  ---------------------------------- */
		void Player::init_tank()
		{
			std::string engineSoundPath = get_asset("tank-move", AssetType::SOUND);
			std::string stopSoundPath = get_asset("tank-stop", AssetType::SOUND);
			std::string idleSoundPath = get_asset("tank-idle", AssetType::SOUND);
			std::string turretSoundPath = get_asset("tank-turret", AssetType::SOUND);
			if (!engineSoundPath.empty())
				engineSound = LoadSound(engineSoundPath.c_str());
			if (!stopSoundPath.empty())
				stopSound = LoadSound(stopSoundPath.c_str());
			if (!idleSoundPath.empty())
				idleSound = LoadSound(idleSoundPath.c_str());
			if (!turretSoundPath.empty())
				turretRotateSound = LoadSound(turretSoundPath.c_str());
			PlaySound(idleSound);
		}
		/* ----------------------------------  Player Settings init  ---------------------------------- */
		void Player::init_player_settings()
		{
			camera.target = controlledTank->position;
			camera.offset = {
				GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
			camera.rotation = 0.0f;
			camera.zoom = maxZoomOut;
		}

		/* ----------------------------------  Player Update Control  ---------------------------------- */
		void Player::updateControl(float dt)
		{
			bool movingNow = IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN) ||
							 IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_RIGHT);
			bool isTurretRotating = IsKeyDown(KEY_Q) || IsKeyDown(KEY_E);
			if (isTurretRotating)
			{
				if (!IsSoundPlaying(turretRotateSound))
				{
					PlaySound(turretRotateSound);
				}
			}
			if (!IsSoundPlaying(idleSound))
			{
				PlaySound(idleSound);
			}
			if (movingNow)
			{
				if (!IsSoundPlaying(engineSound))
				{
					engineVolume = 1.0f;
					PlaySound(engineSound); // start immediately if not already playing
				}
			}
			else
			{
				if (IsSoundPlaying(engineSound))
				{
					engineVolume -= dt * 3.4f; // fade out over 0.5 sec
					if (engineVolume <= 0)
					{
						StopSound(engineSound);
						engineVolume = 0;
					}
					PlaySound(stopSound);
				}
			}
			SetSoundVolume(engineSound, engineVolume);
			wasMoving = movingNow;
			camera.target = controlledTank->position;
			// Zoom in/out with mouse wheel
			float wheel = GetMouseWheelMove();
			if (wheel > 0)
				zoomIn(zoomSpeed);
			else if (wheel < 0)
				zoomOut(zoomSpeed);
			handleMovement(dt);
		}

		void Player::zoomIn(float amount)
		{
			camera.zoom += amount;
			if (camera.zoom > maxZoomIn)
				camera.zoom = maxZoomIn;
		}
		void Player::zoomOut(float amount)
		{
			camera.zoom -= amount;
			if (camera.zoom < maxZoomOut)
				camera.zoom = maxZoomOut;
		}

		void Player::draw()
		{
			if (controlledTank)
			{
				controlledTank->draw();
			}
		}

		/* ----------------------------------  Player Handle Tank movement  ---------------------------------- */
		void Player::handleMovement(float dt)
		{
			if (!controlledTank)
				return;
			if (IsKeyDown(KEY_RIGHT))
				controlledTank->rotation += controlledTank->rotation_speed * dt;
			if (IsKeyDown(KEY_LEFT))
				controlledTank->rotation -= controlledTank->rotation_speed * dt;

			if (IsKeyDown(KEY_UP))
			{
				controlledTank->position.x -= sinf(DEG2RAD * controlledTank->rotation) * controlledTank->movement_speed * dt;
				controlledTank->position.y += cosf(DEG2RAD * controlledTank->rotation) * controlledTank->movement_speed * dt;
			}
			if (IsKeyDown(KEY_DOWN))
			{
				controlledTank->position.x += sinf(DEG2RAD * controlledTank->rotation) * controlledTank->movement_speed * dt;
				controlledTank->position.y -= cosf(DEG2RAD * controlledTank->rotation) * controlledTank->movement_speed * dt;
			}

			if (IsKeyDown(KEY_Q))
			{
				controlledTank->turretRotation -= controlledTank->rotation_speed * dt;
			}
			if (IsKeyDown(KEY_E))
			{
				controlledTank->turretRotation += controlledTank->rotation_speed * dt;
			}

			// Clamp turretRotation
			if (controlledTank->turretRotation < 0)
				controlledTank->turretRotation += 360;
			if (controlledTank->turretRotation >= 360)
				controlledTank->turretRotation -= 360;

			// Clamp body rotation
			if (controlledTank->rotation < 0)
				controlledTank->rotation += 360;
			if (controlledTank->rotation >= 360)
				controlledTank->rotation -= 360;
			// Fire trigger
			if (IsKeyPressed(KEY_SPACE))
			{
				if (controlledTank)
				{
					controlledTank->attack();
				}
			}
			// Call tank updateControl for animations etc.
			if (controlledTank)
			{
				controlledTank->updateControl(dt);
			}
		}
	}

}