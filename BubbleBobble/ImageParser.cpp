#include "ImageParser.h"

std::vector<aze::ImageParser::PointCol> aze::ImageParser::GetPixels(const std::string& inputFile)
{
    std::vector<PointCol> pixelColors;

    // Load image from file
    SDL_Surface* image = IMG_Load(inputFile.c_str());

    // Extract colors from all pixels in image
    Uint32* pixels = (Uint32*)image->pixels;
    Uint8 r, g, b;
    for (int y{ 0 }; y < image->h; ++y)
    {
        for (int x{ 0 }; x < image->w; ++x)
        {
            Uint32 pixel = pixels[x + (y * image->w)];
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            PointCol pc{};
            pc.col = { r, g, b, 255 };
            pc.point = { x, y };
            pixelColors.emplace_back(pc);
        }
    }

    // Free the surface
    SDL_FreeSurface(image);

    return pixelColors;
}
