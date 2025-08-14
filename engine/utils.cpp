#include "base.h"
#include <filesystem>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

namespace Engine {

	// Return the first asset file path that contains `name` in its filename
	// Minimal Resource getter for Adernalin rush game.
	string get_asset(const string& name, const AssetType& asset_type) {
		string default_path = "images";
		switch (asset_type) {
		case(AssetType::IMAGE):
			default_path = "images";
			break;
		case(AssetType::SOUND):
			default_path = "sounds";
			break;
		default:
			default_path = "images";
			break;
		};
		fs::path assets_path = fs::current_path() / "assets" / default_path;
		for (const auto& entry : fs::directory_iterator(assets_path)) {
			if (entry.is_regular_file()) {
				string filename = entry.path().filename().string();
				if (filename.find(name) != string::npos) {
					return entry.path().string();
				}
			}
		}
		return ""; // nothing found
	}

	// return vector of animation sequence files
	AnimationSeq get_animation_seq(const std::string& name) {
		std::vector<Texture2D> animation_files;
		int frame_index = 1;
		fs::path animation_folder = fs::current_path() / "assets" / "images" / name;

		if (!fs::exists(animation_folder) || !fs::is_directory(animation_folder)) {
			return AnimationSeq{ animation_files, 0 };
		}

		while (true) {
			std::string frame_file_name = name + std::to_string(frame_index) + ".png";
			fs::path frame_path = animation_folder / frame_file_name;

			if (!fs::exists(frame_path)) {
				break;
			}

			Texture2D tex = LoadTexture(frame_path.string().c_str());
			if (tex.id == 0) {
				break;
			}

			animation_files.push_back(tex);
			frame_index++;
		}

		return AnimationSeq{ animation_files, static_cast<int>(animation_files.size()) };
	}

}