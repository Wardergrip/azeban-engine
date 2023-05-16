#pragma once
#include "Command.h"
#include "SoundSystem.h"
#include <string>

namespace aze
{
	class AudioPlayCommand : public Command
	{
	public:
		AudioPlayCommand(SoundSystem* pSoundSystem, const std::string& filePath, float volume)
			:m_pSoundSystem{pSoundSystem}, m_FilePath{filePath}, m_Volume{volume}
		{
		}

		void Execute() override
		{
			m_pSoundSystem->Play(m_FilePath, m_Volume);
		}

	private:
		SoundSystem* const m_pSoundSystem;
		const std::string m_FilePath;
		const float m_Volume;
	};
}