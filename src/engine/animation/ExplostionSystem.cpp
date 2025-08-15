#include "ExplostionSystem.hpp"
#include "../base.hpp"

namespace Engine
{
	namespace Animation
	{

		std::vector<ExplostionSystem *> ExplostionSystem::global_explosions;

		void ExplostionSystem::loadTexture(const std::string &name, const AnimationSpiritFMT &type)
		{
			default_fmt = type;
			std::string path = get_asset(name);
			if (path.empty())
				return;

			explosionTexture = LoadTexture(path.c_str());

			switch (default_fmt)
			{
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
				break;
			case AnimationSpiritFMT::_MULTIFILES:
				return;
			}

			frameWidth = explosionTexture.width / framesPerRow;
			frameHeight = explosionTexture.height / (totalFrames / framesPerRow);

			loadExplostionSound();
		}

		void ExplostionSystem::loadExplostionSound(const std::string name)
		{
			std::string s_path = get_asset(name, AssetType::SOUND);
			if (!s_path.empty())
				explostionSound = LoadSound(s_path.c_str());
		}

		void ExplostionSystem::start(const Vector2 &pos, bool loopAnim)
		{
			ExplosionInstance inst;
			PlaySound(explostionSound);
			inst.position = pos;
			inst.loop = loopAnim;
			inst.currentFrame = 0;
			inst.frameTimer = 0.0f;
			activeExplosions.push_back(inst);

			// Add to global layer
			global_explosions.push_back(this);
		}

		void ExplostionSystem::update(float dt)
		{
			for (auto it = activeExplosions.begin(); it != activeExplosions.end();)
			{
				it->frameTimer += dt;
				if (it->frameTimer >= frameTime)
				{
					it->frameTimer = 0.0f;
					it->currentFrame++;
					if (it->currentFrame >= totalFrames)
					{
						if (it->loop)
							it->currentFrame = 0;
						else
						{
							it = activeExplosions.erase(it);
							continue;
						}
					}
				}
				++it;
			}
		}

		void ExplostionSystem::draw() const
		{
			for (const auto &e : activeExplosions)
			{
				if (e.currentFrame >= totalFrames)
					continue;

				int fx = (e.currentFrame % framesPerRow) * frameWidth;
				int fy = (e.currentFrame / framesPerRow) * frameHeight;
				Rectangle srcRec{(float)fx, (float)fy, (float)frameWidth, (float)frameHeight};

				float scaledW = frameWidth * scale;
				float scaledH = frameHeight * scale;
				Vector2 origin{scaledW / 2.0f, scaledH / 2.0f};
				Rectangle dest{e.position.x, e.position.y, scaledW, scaledH};

				DrawTexturePro(explosionTexture, srcRec, dest, origin, 0.0f, WHITE);
			}
		}

	} // namespace Animation
} // namespace Engine
