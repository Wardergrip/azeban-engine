#pragma once

struct SDL_Surface;
namespace aze
{
	/**
	 * Simple RAII wrapper for an SDL_Surface
	 */
	class Surface2D
	{
	public:
		explicit Surface2D(SDL_Surface* pSurface);
		~Surface2D();

		SDL_Surface* GetSDLSurface() const;

		Surface2D(const Surface2D&) = delete;
		Surface2D(Surface2D&&) = delete;
		Surface2D& operator= (const Surface2D&) = delete;
		Surface2D& operator= (const Surface2D&&) = delete;
	private:
		SDL_Surface* m_pSurface;
	};
}