#pragma once
#include <sol/sol.hpp>

namespace Engine
{
    namespace Scripting
    {

        class LuaBindings
        {
        public:
            static void register_all(sol::state &lua);
        };

    }
}
