#include "ExplostionSystem.h"

namespace Engine {
	namespace Animation {
		/* ---------------------------------- Load Texture ---------------------------------- */
		void ExplostionSystem::loadTexture(const std::string& name) {
			std::string path = get_asset(name);
			if (!path.empty()) {
				explosionTexture = LoadTexture(path.c_str());
			}
			switch (default_fmt) {
			case AnimationSpiritFMT::_64GRID:
				break;
			case AnimationSpiritFMT::_32GRID:
				break;
			case AnimationSpiritFMT::_16GRID:
				break;
			case AnimationSpiritFMT::_8GRID:
				break;
			case AnimationSpiritFMT::_4GRID:
				break;
			}
		}

		/* ----------------------------------  Update Explostion Frames   ---------------------------------- */
		void ExplostionSystem::update(float dt, const Vector2& pos) {

		}

	}
}