#pragma once
#include "../base.h"
#include <vector>
#include <string>

namespace Engine {
	// A single track imprint
	struct TankTrackStamp {
		Vector2 pos;
		float rotation = 0.0f;
		float age = 0.0f;           // Time alive in seconds
		float lifetime = 0.0f;      // How long before fade-out
		float startDistance = 30.0f; // Distance travelled when created
		float alpha = 1.0f;         // Current transparency (0-1)
	};

	struct TankTireSystem {
		// Visuals
		Texture2D trackTexture{};                // Tire track image
		std::vector<TankTrackStamp> tireTracks;  // Active stamps
		float distSinceLastStamp = 0.0f;
		// Placement & spacing
		float trackSpacing = 20.0f;          // px between successive stamps
		float trackScale = 0.5f;             // visual scale (tweak)
		float trackLateralOffset = 30.0f;    // left/right offset from center in local coords
		
		// Lifetime settings
		float trackLifetime = 6.0f;          // seconds to fade out
		float trackLifeDistance = 400.0f;    // alternative: fade by path distance (px)
		bool useDistanceBasedFade = false;   // toggle fade-by-distance or fade-by-time

		// Tracking movement
		float totalDistanceTravelled = 0.0f; // accumulate traveled distance
		Vector2 prevPositionForTracks{ 0, 0 }; // used to compute traveled delta

		// Limits
		size_t maxTrackCount = 500;          // safety cap

		// Methods
		Vector2 getWheelWorldPos(const Vector2& tankPos, float rotationDeg, const Vector2& wheelLocalOffset);
		void loadTrackTexture(const std::string& assetName);
		void addTrackStamp(const Vector2& worldPos, float rotation);
		void update(float dt, const Vector2& currentPos, float rotation);
		void draw() const;
	};

	// Helper to calculate distance between two Vector2s
	inline float Vector2Distance(const Vector2& a, const Vector2& b) {
		float dx = b.x - a.x;
		float dy = b.y - a.y;
		return sqrtf(dx * dx + dy * dy);
	}
}
