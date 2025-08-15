#pragma once
#include "tank.hpp"

namespace Engine
{
    namespace Player
    {
        class Player
        {
        public:
            Player(BaseTank *tank);
            ~Player();
            void updateControl(float dt);
            void draw();
            void zoomIn(float amount);
            void zoomOut(float amount);
            Camera2D camera{};

        private:
            /* ----------------------------------  Player Tank attributes  ---------------------------------- */
            BaseTank *controlledTank;
            void handleMovement(float dt);
            void init_tank();
            void init_player_settings();
            Sound engineSound{};
            float engineVolume = 1.0f;
            Sound stopSound{};
            Sound idleSound{};
            Sound turretRotateSound{};
            bool isMoving = false;
            bool wasMoving = false;
            /* ----------------------------------  Player Camera Attributes ---------------------------------- */
            float maxZoomIn = 2.0f;
            float maxZoomOut = 0.5f;
            float zoomSpeed = 0.1f;
        };
    }
}