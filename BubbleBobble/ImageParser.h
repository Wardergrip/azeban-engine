#pragma once
#include <vector>
#include <utility>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

namespace aze
{
	class ImageParser final
	{
	public:
		ImageParser() = delete;

		struct PointCol
		{
			SDL_Point point;
			SDL_Color col;
		};

		static std::vector<PointCol> GetPixels(const std::string& inputFile);
	};
}

