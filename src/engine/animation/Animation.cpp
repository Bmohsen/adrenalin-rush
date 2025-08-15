#include "../base.hpp"
#include "Animation.hpp"
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

namespace Engine
{
	namespace Animation
	{
		// return vector of animation sequence files
		AnimationSeq AnimationUtil::get_animation_seq(const std::string &name)
		{
			std::vector<Texture2D> animation_files;
			int frame_index = 1;
			fs::path animation_folder = fs::current_path() / "assets" / "images" / name;

			if (!fs::exists(animation_folder) || !fs::is_directory(animation_folder))
			{
				return AnimationSeq{animation_files, 0};
			}

			while (true)
			{
				std::string frame_file_name = name + std::to_string(frame_index) + ".png";
				fs::path frame_path = animation_folder / frame_file_name;

				if (!fs::exists(frame_path))
				{
					break;
				}

				Texture2D tex = LoadTexture(frame_path.string().c_str());
				if (tex.id == 0)
				{
					break;
				}

				animation_files.push_back(tex);
				frame_index++;
			}

			return AnimationSeq{animation_files, static_cast<int>(animation_files.size())};
		}
	}
}