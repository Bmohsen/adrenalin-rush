#include "../base.h" 
#include "tank_tire_system.h"



namespace Engine {

	void TankTireSystem::loadTrackTexture(const std::string& assetName) {
		std::string trackPath = get_asset(assetName);
		if (!trackPath.empty()) {
			trackTexture = LoadTexture(trackPath.c_str());
		}
	}

	void TankTireSystem::addTrackStamp(const Vector2& worldPos, float rotation) {
		if (trackTexture.id == 0) return;

		TankTrackStamp stamp;
		stamp.pos = worldPos;
		stamp.rotation = rotation;
		stamp.age = 0.0f;
		stamp.lifetime = trackLifetime;
		stamp.startDistance = totalDistanceTravelled;
		stamp.alpha = 1.0f;

		if (tireTracks.size() > maxTrackCount) {
			tireTracks.erase(tireTracks.begin()); // Remove oldest
		}
		tireTracks.push_back(stamp);
	}

    Vector2 TankTireSystem::getWheelWorldPos(const Vector2& tankPos, float rotationDeg, const Vector2& wheelLocalOffset) {
        float rad = DEG2RAD * rotationDeg;
        Vector2 rotated = {
            wheelLocalOffset.x * cosf(rad) + trackLateralOffset - wheelLocalOffset.y * sinf(rad),
            wheelLocalOffset.x * sinf(rad) + trackLateralOffset + wheelLocalOffset.y * cosf(rad)
        };
        return { tankPos.x + rotated.x, tankPos.y + rotated.y };
    }

    void TankTireSystem::update(float dt, const Vector2& currentPos, float rotation) {
        // Initialize prev position if needed
        if (prevPositionForTracks.x == 0 && prevPositionForTracks.y == 0) {
            prevPositionForTracks = currentPos;
        }

        // Calculate distance travelled this frame
        float distance = Vector2Distance(prevPositionForTracks, currentPos);
        totalDistanceTravelled += distance;
        prevPositionForTracks = currentPos;

        // Accumulate distance for stamping tracks
        distSinceLastStamp += distance;

        if (distSinceLastStamp >= trackSpacing) {
            distSinceLastStamp = 0.0f;

            float rad = DEG2RAD * rotation;
            // Rotate offsets by tank rotation
            auto rotatePoint = [&](const Vector2& p) -> Vector2 {
                return {
                    p.x * cosf(rad) - p.y * sinf(rad),
                    p.x * sinf(rad) + p.y * cosf(rad)
                };
                };
            Vector2 leftWorldPos = getWheelWorldPos(currentPos, rotation, { -trackLateralOffset, 0.0f });
            Vector2 rightWorldPos = getWheelWorldPos(currentPos, rotation, { trackLateralOffset, 0.0f });
            addTrackStamp(leftWorldPos, rotation);
            addTrackStamp(rightWorldPos, rotation);
            // Add track stamps at world position plus offset
        /*    addTrackStamp({ currentPos.x + leftWorldOffset.x, currentPos.y + leftWorldOffset.y }, rotation);
            addTrackStamp({ currentPos.x + rightWorldOffset.x, currentPos.y + rightWorldOffset.y }, rotation);*/
        }

        // Update fading and lifetime of track stamps
        for (auto it = tireTracks.begin(); it != tireTracks.end();) {
            it->age += dt;
            if (useDistanceBasedFade) {
                // Fade based on distance travelled since the stamp was created
                float distSinceStamp = totalDistanceTravelled - it->startDistance;
                it->alpha = 1.0f - (distSinceStamp / trackLifeDistance);
            }
            else {
                // Fade based on time alive
                it->alpha = 1.0f - (it->age / it->lifetime);
            }

            if (it->alpha <= 0.0f) {
                it = tireTracks.erase(it);
            }
            else {
                ++it;
            }
        }
    }

	static inline float Clamp(float v, float a, float b) {
		return (v < a) ? a : (v > b) ? b : v;
	}
	void TankTireSystem::draw() const {
		if (trackTexture.id == 0) return;

		Rectangle src = { 0.0f, 0.0f, (float)trackTexture.width, (float)trackTexture.height };

		for (const auto& stamp : tireTracks) {
			float dstW = trackTexture.width * trackScale;
			float dstH = trackTexture.height * trackScale;

			Rectangle dst = {
				stamp.pos.x - dstW * 0.5f,    // top-left so the stamp is centered at stamp.pos
				stamp.pos.y - dstH * 0.5f,
				dstW,
				dstH
			};

			Vector2 origin = { dstW * 0.5f, dstH * 0.5f };
			Color tint = WHITE;
			tint.a = (unsigned char)(Clamp(stamp.alpha, 0.0f, 1.0f) * 255.0f);

			DrawTexturePro(trackTexture, src, dst, origin, stamp.rotation, tint);
		}
	}
}