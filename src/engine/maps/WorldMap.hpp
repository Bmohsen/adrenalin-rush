#pragma once

#include "../base.hpp"
#include <string>

namespace Engine
{
	namespace Map
	{

		class WorldMap
		{
		public:
			WorldMap();
			~WorldMap();

			// Returns the current map index or ID
			int get_map();

			// Called to start the map (may invoke Lua hooks)
			void start_map();

			// Loads the Lua script for the given map name
			// Returns false if load fails
			bool load_map(const std::string &name);

		private:
			int current_map = 0; // Default to first map; adjust as needed
		};

	}
}
