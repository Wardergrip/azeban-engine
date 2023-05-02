#include "Surface2D.h"
#include <SDL_image.h>

aze::Surface2D::Surface2D(SDL_Surface* pSurface)
{
	m_pSurface = pSurface;
}

aze::Surface2D::~Surface2D()
{
	SDL_FreeSurface(m_pSurface);
}

SDL_Surface* aze::Surface2D::GetSDLSurface() const
{
	return m_pSurface;
}
