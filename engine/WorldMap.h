#pragma once

namespace Engine {
	class WorldMap
	{
	public:
		WorldMap();
		virtual ~WorldMap();
		int get_map();
		void start_map();
		virtual void load() = 0;        // Load map assets, spawn objects, etc.
		virtual void start() = 0;       // Initialize map state
		virtual void update(float dt) = 0;  // Update game logic per frame
		virtual void render() = 0;      // Draw map & objects
		virtual int getMapID() const = 0;  // Return map identifier
	private:
		int current_map{ 1 };
		void load_map();
	};

}