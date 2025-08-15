#pragma once
#include "../base.hpp"

namespace Engine
{
	namespace Animation
	{
		struct AnimationSeq
		{
			std::vector<Texture2D> animations;
			int frame_counts;
		};
		struct AnimationUtil
		{
			static AnimationSeq get_animation_seq(const std::string &name);
		};
	}
}