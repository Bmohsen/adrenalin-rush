#pragma once
#include "../base.h"

namespace Engine {
	namespace Animation {

		enum class AnimationSpiritFMT {
			_64GRID,
			_32GRID,
			_16GRID,
			_8GRID,
			_4GRID,
			_MULTIFILES
		};

		struct ExplostionSystem {
			AnimationSpiritFMT default_fmt{ AnimationSpiritFMT::_64GRID };
			Texture2D explosionTexture{};
			std::vector<Texture2D> frames{};
			int framesPerRow = 8;
			int currentFrame = 0;
			float frameTime = 0.05f;
			float frameTimer = 0.0f;
			float explosionScale = 1.0f;
			Vector2 position{ 0.0f, 0.0f };
			bool active{ false };
			bool loop{ false };
			void loadTexture(const std::string& name);
			void update(float dt);
			void draw() const;
			void start(const Vector2& pos, bool loopAnim = false);
		};
	}
}
