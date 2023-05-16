#pragma once
#include "SoundSystem.h"
#include <memory>
#include <iostream>
#include <sstream>

namespace aze
{
	class SoundSystemLogger final : public SoundSystem
	{
	public:
		SoundSystemLogger(std::unique_ptr<SoundSystem> pSoundSystem)
			:m_pSoundSystem{ std::move(pSoundSystem) }
		{
		}

		virtual void Play(const std::string& fileName, float volume)
		{
			std::stringstream ss;
			ss << "[SoundSystemLogger] " << "{Play} " << "FileName: " << fileName << " at " << volume << " volume\n";
			std::cout << ss.str();
			m_pSoundSystem->Play(fileName, volume);
		}
		virtual void SetMute(bool state)
		{
			std::stringstream ss;
			ss << "[SoundSystemLogger] " << "{SetMute} " << "New state: " << std::boolalpha << state << '\n';
			std::cout << ss.str();
			m_pSoundSystem->SetMute(state);
		}
		virtual bool IsMuted() const
		{
			bool muted{ m_pSoundSystem->IsMuted() };
			std::stringstream ss;
			ss << "[SoundSystemLogger] " << "{IsMuted} " << "Current state: " << std::boolalpha << muted << '\n';
			std::cout << ss.str();
			return muted;
		}

	private:
		std::unique_ptr<SoundSystem> m_pSoundSystem;
	};
}