#pragma once
#include <vector>
#include <string>
#include <memory>
#include <SDL.h>


namespace aze
{
	class Surface2D;
	class ImageParser final
	{
	public:
		ImageParser(const std::string& inputFile);

		struct PointCol
		{
			SDL_Point point;
			SDL_Color col;
		};

		const std::vector<PointCol>& GetPixels();
		size_t GetWidth() const;
		size_t GetHeight() const;

	private:
		std::string m_InputFile;
		std::vector<PointCol> m_Pixels;
		std::shared_ptr<Surface2D> m_Image;
	};
}

