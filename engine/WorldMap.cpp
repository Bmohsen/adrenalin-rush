#include "WorldMap.h"
namespace Engine {
	WorldMap::WorldMap() {};
	WorldMap::~WorldMap() {};
	int WorldMap::get_map(){
		return current_map;
	}
	void WorldMap::start_map(){}
	void WorldMap::load_map(){}
}