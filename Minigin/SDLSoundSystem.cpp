#include "SDLSoundSystem.h"
#include <thread>
#include <mutex>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <atomic>

namespace aze
{
	struct AudioRequest
	{
		std::string filePath;
		float volume;
		int loops;
	};

	class SDLSoundSystem::SDLSoundSystemImpl final : public SoundSystem
	{
	public:
		SDLSoundSystemImpl()
		{
			const int sdlInitResult{ SDL_Init(SDL_INIT_AUDIO) };
			if (sdlInitResult != 0)
			{
				std::string errorMessage{ "SDL Audio Initialization failed" };
				errorMessage += SDL_GetError();
				std::cout << errorMessage << '\n';
				return;
			}

			const int audioInitResult{ Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 4096) };
			if (audioInitResult != 0)
			{
				std::string errorMessage{ "SDL Mixer Initialization failed" };
				errorMessage += Mix_GetError();
				std::cout << errorMessage << '\n';
				return;
			}

			m_Thread = std::jthread{ [&]() { AudioThreadLoop(); } };
		}
		virtual ~SDLSoundSystemImpl()
		{
			m_IsExiting = true;
			m_ThreadCondition.notify_one();
			for (auto& [path,pChunk] : m_SoundMap)
			{
				Mix_FreeChunk(pChunk);
			}
			m_SoundMap.clear();
			// Explicitely join thread to prevent thread reading destroyed class.
			m_Thread.join();
		}

		// SoundSystem interface
		virtual void Play(const std::string& fileName, float volume, int loops) override
		{
			const std::lock_guard lock{ m_Mutex };
			m_RequestQueue.push(AudioRequest{ fileName,volume,loops });
			m_ThreadCondition.notify_one();
		}
		virtual void SetMute(bool state) override
		{
			if (state == m_IsMuted) return;
			m_IsMuted = state;

			for (int channelId : m_Channels)
			{
				Mix_Volume(channelId, state ? 0 : MIX_MAX_VOLUME);
			}
		}
		virtual bool IsMuted() const
		{
			return m_IsMuted;
		}

		void AudioThreadLoop()
		{
			while (m_IsExiting == false)
			{
				std::unique_lock lock(m_Mutex);
				m_ThreadCondition.wait(lock, [&] { return (m_RequestQueue.size() > 0) || m_IsExiting; });

				while (m_RequestQueue.size() > 0)
				{
					AudioRequest request{ m_RequestQueue.front() };
					lock.unlock();

					if (!m_SoundMap.contains(request.filePath))
					{
						Mix_Chunk* pAudio = Mix_LoadWAV(request.filePath.c_str());
						if (pAudio == nullptr)
						{
							throw std::runtime_error("File not found: " + request.filePath + "SDL Error: " + Mix_GetError());
						}
						m_SoundMap[request.filePath] = pAudio;
					}
					Mix_Chunk* pAudio = m_SoundMap[request.filePath];

					// Set audio for the chunk to the desired volume
					Mix_VolumeChunk(pAudio, std::clamp(static_cast<int>(request.volume * MIX_MAX_VOLUME), 0, MIX_MAX_VOLUME));
					const int channel = Mix_PlayChannel(-1, pAudio, request.loops);
					Mix_Volume(channel, m_IsMuted ? 0 : MIX_MAX_VOLUME);

					// If we were not able to play (no available channels)
					// Return. The request is still at the start of the queue
					if (channel == -1) return;
					// Request was succesfull, we can already remove it from the queue
					lock.lock();
					m_RequestQueue.pop();
					lock.unlock();
					
					m_Channels.emplace(channel);
				}
			}
		}

	private:
		std::queue<AudioRequest> m_RequestQueue{};
		std::unordered_map<std::string, Mix_Chunk*> m_SoundMap{};
		std::unordered_set<int> m_Channels{};

		std::jthread m_Thread;
		std::mutex m_Mutex{};
		std::condition_variable m_ThreadCondition{};
		std::atomic<bool> m_IsMuted{ false };
		std::atomic<bool> m_IsExiting{ false };
	};
}

aze::SDLSoundSystem::SDLSoundSystem()
{
	m_pImpl = std::make_unique<SDLSoundSystemImpl>();
}

aze::SDLSoundSystem::~SDLSoundSystem() = default;

void aze::SDLSoundSystem::Play(const std::string& fileName, float volume, int loops)
{
	m_pImpl->Play(fileName, volume,loops);
}

void aze::SDLSoundSystem::SetMute(bool state)
{
	m_pImpl->SetMute(state);
}

bool aze::SDLSoundSystem::IsMuted() const
{
	return m_pImpl->IsMuted();
}
