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
			int framesPerRow = 8;
			int currentFrame = 0;
			float frameTime = 0.05f;
			float frameTimer = 0.0f;
			float explosionScale = 1.0f;
			void loadTexture(const std::string& name);
			void update(float dt, const Vector2& pos);
			void draw() const;
		};
	}
}
