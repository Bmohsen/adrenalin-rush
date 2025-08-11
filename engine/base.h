#pragma once

#include <raylib.h>
#include <string>
#include <vector>

namespace Engine {
	enum class AssetType {
		IMAGE,
		SOUND
	};

	struct AnimationSeq {
		std::vector<Texture2D> animations;
		int frame_counts;
	};

	std::string get_asset(const std::string& name, const AssetType& asset_type = AssetType::IMAGE);

	AnimationSeq get_animation_seq(const std::string& name);
}