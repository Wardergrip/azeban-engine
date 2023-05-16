#pragma once
#include <string>

namespace aze
{
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;

		virtual void Play(const std::string& fileName, float volume) = 0;
		virtual void SetMute(bool state) = 0;
		virtual bool IsMuted() const = 0;
	};

	class DefaultSoundSystem final : public SoundSystem
	{
	public:
		virtual void Play(const std::string&, float) override {}
		virtual void SetMute(bool) override {}
		virtual bool IsMuted() const { return true; };
	};
}