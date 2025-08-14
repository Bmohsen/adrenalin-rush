#include "ExplostionSystem.h"

namespace Engine {
	namespace Animation {
		/* ---------------------------------- Load Texture ---------------------------------- */
		void ExplostionSystem::loadTexture(const std::string& name) {
			std::string path = get_asset(name);
			if (path.empty()) return;
			explosionTexture = LoadTexture(path.c_str());
			// we are using pre-slice, not memory effienet but easier to implant, less head ache later.
			int totalFrames = 0;
			switch (default_fmt) {
			case AnimationSpiritFMT::_64GRID:
				framesPerRow = 8;
				totalFrames = 64;
				break;
			case AnimationSpiritFMT::_32GRID:
				framesPerRow = 8;
				totalFrames = 32;
				break;
			case AnimationSpiritFMT::_16GRID:
				framesPerRow = 4;
				totalFrames = 16;
				break;
			case AnimationSpiritFMT::_8GRID:
				framesPerRow = 4;
				totalFrames = 8;
				break;
			case AnimationSpiritFMT::_4GRID:
				framesPerRow = 2;
				totalFrames = 4;
			case AnimationSpiritFMT::_MULTIFILES:
				// load separate images elsewhere, 
				// so skip slicing
				// move AnimationSeq here, it fits here not util
				return;
			}

			frames.clear();
			int frameW{ explosionTexture.width / framesPerRow };
			int frameH{ explosionTexture.height / ( totalFrames / framesPerRow) };
			Image sheetImage = LoadImage(path.c_str());
			for (int i = 0; i < totalFrames; i++)
			{
				int fx = (i % framesPerRow) * frameW;
				int fy = (i / framesPerRow) * frameH;

				Image frameImg = ImageFromImage(sheetImage, { (float)fx, (float)fy, (float)frameW, (float)frameH });
				Texture2D frameTexture = LoadTextureFromImage(frameImg);
				frames.push_back(frameTexture);
				UnloadImage(frameImg);
			}	
			UnloadImage(sheetImage); 

		}

		/* ---------------------------------- Start Explosion ---------------------------------- */
		void ExplostionSystem::start(const Vector2& pos, bool loopAnim) {
			position = pos;
			currentFrame = 0;
			frameTimer = 0.0f;
			loop = loopAnim;
			active = true;
		}

		/* ---------------------------------- Update Explosion Frames ---------------------------------- */
		void ExplostionSystem::update(float dt) {
			if (!active) return;

			frameTimer += dt;
			if (frameTimer >= frameTime) {
				frameTimer = 0.0f;
				currentFrame++;

				if (currentFrame >= (int)frames.size()) {
					if (loop) {
						currentFrame = 0;
					}
					else {
						active = false;
					}
				}
			}
		}

		/* ---------------------------------- Draw Explosion ---------------------------------- */
		void ExplostionSystem::draw() const {
			if (!active || frames.empty()) return;

			const Texture2D& frameTex = frames[currentFrame];
			Vector2 origin{ frameTex.width / 2.0f, frameTex.height / 2.0f };

			DrawTexturePro(
				frameTex,
				{ 0.0f, 0.0f, (float)frameTex.width, (float)frameTex.height },
				{ position.x, position.y, frameTex.width * explosionScale, frameTex.height * explosionScale },
				origin,
				0.0f,
				WHITE
			);
		}

	}

}