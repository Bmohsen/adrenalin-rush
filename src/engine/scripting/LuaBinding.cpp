#include "LuaBinding.hpp"
#include "../maps/WorldMap.hpp"

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

            // Later: register Player, Enemy, Physics, etc.
        }

    }
}
