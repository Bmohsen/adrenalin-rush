#include "LuaBinding.hpp"
#include "../maps/WorldMap.hpp"
#include <sol/sol.hpp>

namespace Engine
{
    namespace Scripting
    {
        void LuaBindings::register_all(sol::state &lua)
        {
            lua.new_usertype<Engine::Map::WorldMap>(
                "WorldMap",
                sol::constructors<Engine::Map::WorldMap()>(),
                "get_map", &Engine::Map::WorldMap::get_map,
                "start_map", &Engine::Map::WorldMap::start_map,
                "load_map", &Engine::Map::WorldMap::load_map);

            lua.set_function("load_mission", [](Engine::Map::WorldMap &map, const std::string &mission_name)
                             {
                if (map.load_map(mission_name)) {
                    map.start_map();
                } else {
                    throw std::runtime_error("Failed to load mission: " + mission_name);
                } });
        }
    }
}
