#pragma once
#include "Command.h"
#include "SoundSystem.h"
#include <iostream>
#include <string>

namespace aze
{
	class MuteCommand : public Command
	{
	public:
		MuteCommand(SoundSystem* pSoundSystem)
			:m_pSoundSystem{ pSoundSystem }
		{
		}

		void Execute() override
		{
			auto isMuted = m_pSoundSystem->IsMuted();
			m_pSoundSystem->SetMute(!isMuted);
		}

	private:
		SoundSystem* const m_pSoundSystem;
	};
}