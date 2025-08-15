#pragma once
#include "../base.hpp"

// TODO: Make the explosion generic type so we can pass different textures
namespace Engine
{
    namespace Animation
    {
        enum class AnimationSpiritFMT
        {
            _64GRID,
            _32GRID,
            _16GRID,
            _8GRID,
            _4GRID,
            _MULTIFILES
        };

        class ExplostionSystem
        {
        public:
            void loadTexture(const std::string &name, const AnimationSpiritFMT &type);
            void loadExplostionSound(const std::string name = "tank-bomb");
            void start(const Vector2 &pos, bool loopAnim = false);
            void update(float dt);
            void draw() const;
            float scale{1.0f};
            float frameTime{0.01f};
            Sound explostionSound{};

        private:
            struct ExplosionInstance
            {
                Vector2 position;
                int currentFrame{0};
                float frameTimer{0.0f};
                bool loop{false};
            };

            AnimationSpiritFMT default_fmt{AnimationSpiritFMT::_64GRID};
            Texture2D explosionTexture{};
            int framesPerRow{0};
            int totalFrames{0};
            int frameWidth{0};
            int frameHeight{0};

            std::vector<ExplosionInstance> activeExplosions;
        };
    }
}
