#pragma once

#include <raylib.h>
#include <string>


enum class AssetType {
	IMAGE,
	SOUND
};

std::string get_asset(const std::string& name, const AssetType& asset_type= AssetType::IMAGE);