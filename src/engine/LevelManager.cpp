#include "base.hpp"
#include "tank.hpp"

namespace Engine
{
	class LevelManager
	{
	public:
		// handle tanks level up, each type of tank has different point gain of xp @TODO: later
		void handleLevelUp(BaseTank *tank)
		{
			switch (tank->tank_class)
			{
			case TankClass::LIGHT:
				break;
			case TankClass::MEDIUM:
				break;
			case TankClass::HEAVY:
				break;
			};
		}
	};

}