#include "ImageParser.h"
#include "ResourceManager.h"
#include <SDL_image.h>
#include "Surface2D.h"

#include <iostream>

aze::ImageParser::ImageParser(const std::string& inputFile)
    :m_InputFile{inputFile}
{
    // Load image from file
    m_Image = ResourceManager::GetInstance().LoadSurface(inputFile);
   
    auto sdlImage = m_Image->GetSDLSurface();
    // Extract colors from all pixels in image
    SDL_LockSurface(sdlImage);
    Uint32* pixels = (Uint32*)sdlImage->pixels;
    Uint8 r, g, b;
    for (int y{ 0 }; y < sdlImage->h; ++y)
    {
        for (int x{ 0 }; x < sdlImage->w; ++x)
        {
            Uint32 pixel = pixels[x + (y * sdlImage->w)];
            SDL_GetRGB(pixel, sdlImage->format, &r, &g, &b);
            PointCol pc{};
            pc.col = { r, g, b, 255 };
            pc.point = { x, y };
            m_Pixels.emplace_back(pc);
        }
    }
    SDL_UnlockSurface(sdlImage);

    /*std::cout << "Done parsing image:\n";
    int p{0};
    for (auto& pixel : m_Pixels)
    {
        std::cout << "[" << p << "] P: " 
            << pixel.point.x << " , " << pixel.point.y 
            << " Col: " << pixel.col.r << " , " << pixel.col.g << " , " << pixel.col.b << "\n";
        ++p;
    }
    std::cout << "\n\n\n";*/
}

const std::vector<aze::ImageParser::PointCol>& aze::ImageParser::GetPixels()
{
    return m_Pixels;
}

size_t aze::ImageParser::GetWidth() const
{
    return m_Image->GetSDLSurface()->w;
}

size_t aze::ImageParser::GetHeight() const
{
    return m_Image->GetSDLSurface()->h;
}
