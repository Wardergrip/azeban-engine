#pragma once
#include "Singleton.h"
#include <memory>

#include "SoundSystem.h"

namespace aze
{
	class ServiceManager final : public Singleton<ServiceManager>
	{
	public:
		SoundSystem& GetSoundSystem() 
		{ 
			return *m_SoundSystem; 
		}
		void RegisterSoundSystem(std::unique_ptr<SoundSystem> ss) 
		{
			m_SoundSystem = std::move(ss);
		}

		void UnregisterSoundSystem()
		{
			m_SoundSystem = std::move(std::unique_ptr<SoundSystem>(new DefaultSoundSystem()));
		}
	private:
		friend class Singleton<ServiceManager>;
		ServiceManager()
			:m_SoundSystem{ new DefaultSoundSystem() }
		{
		}

		std::unique_ptr<SoundSystem> m_SoundSystem;
	};
}