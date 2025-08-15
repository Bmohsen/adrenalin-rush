#pragma once

#include <raylib.h>
#include <string>
#include <vector>

namespace Engine
{
	enum class AssetType
	{
		IMAGE,
		SOUND,
		MAP
	};

	std::string get_asset(const std::string &name, const AssetType &asset_type = AssetType::IMAGE);

}