#include "../base.hpp"
#include "WorldMap.hpp"
#include "../scripting/LuaBinding.hpp"
#include <sol/sol.hpp>

namespace Engine
{
	namespace Map
	{

		sol::state lua;

		WorldMap::WorldMap() {};
		WorldMap::~WorldMap() {};

		int WorldMap::get_map()
		{
			return current_map;
		}

		void WorldMap::start_map()
		{
			// Example: call Lua function "on_start" if it exists
			if (lua["on_start"].valid())
			{
				lua["on_start"]();
			}
		}

		bool WorldMap::load_map(const std::string &name)
		{
			std::string map_path = get_asset(name, AssetType::MAP);
			if (map_path.empty())
				return false;

			lua.open_libraries(sol::lib::base);
			Engine::Scripting::LuaBindings::register_all(lua);

			auto result = lua.script_file(map_path.c_str());
			if (!result.valid())
			{
				sol::error err = result;
				std::cerr << "Lua error: " << err.what() << "\n";
				return false;
			}

			return true;
		}

	}
}
