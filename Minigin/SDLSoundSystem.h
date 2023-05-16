#pragma once
#include "SoundSystem.h"
#include <memory>

namespace aze
{
	class SDLSoundSystem final : public SoundSystem
	{
	public:
		SDLSoundSystem();
		SDLSoundSystem(SDLSoundSystem&& other) = delete;
		SDLSoundSystem(const SDLSoundSystem& other) = delete;
		SDLSoundSystem& operator=(SDLSoundSystem&& other) = delete;
		SDLSoundSystem& operator=(const SDLSoundSystem& other) = delete;
		virtual ~SDLSoundSystem();

		// SoundSystem interface
		virtual void Play(const std::string& fileName, float volume) override;
		virtual void SetMute(bool state) override;
		virtual bool IsMuted() const;

	private:
		class SDLSoundSystemImpl;
		std::unique_ptr<SDLSoundSystemImpl> m_pImpl;
	};
}

