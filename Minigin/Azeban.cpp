#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Azeban.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "GameTime.h"

#include <chrono>
#include <thread>

#include <iostream>

#undef min
#undef max

constexpr int WINDOW_WIDTH{ 769 };
constexpr int WINDOW_HEIGHT{ 673 };

SDL_Window* g_window{};

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

aze::Azeban::Azeban(const std::string &dataPath)
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);
}

aze::Azeban::~Azeban()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void aze::Azeban::Run(const std::function<void()>& load)
{
	load();

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();
	auto& gameTime = GameTime::GetInstance();

	bool doContinue = true;
	std::chrono::steady_clock::time_point currentTime;
	std::chrono::steady_clock::time_point lastTime;
	const constexpr int targetFps{ 144 };
	const constexpr float physicsTimeStep{1 / 60.f};
	gameTime.SetFixedTimeStep(physicsTimeStep);
	constexpr int maxWaitingTimeMs{ static_cast<int>(1000 / targetFps) };
	float lag{ 0.0f };
	sceneManager.Start();
	while (doContinue)
	{
		currentTime = std::chrono::high_resolution_clock::now();
		const float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
		doContinue = input.ProcessInput();
		gameTime.SetElapsed(deltaTime);

		lag += deltaTime;
		while (lag >= gameTime.GetFixedTimeStep())
		{
			// First time, lastTime is 0, which means deltaTime is very high, which messes this loop up
			if (deltaTime >= 1000.0f) lag = gameTime.GetFixedTimeStep();
			sceneManager.FixedUpdate();
			lag -= gameTime.GetFixedTimeStep();
		}
		sceneManager.Update();
		renderer.Render();

		lastTime = currentTime;
		
		const auto sleepTime{ currentTime + std::chrono::milliseconds(maxWaitingTimeMs) - std::chrono::high_resolution_clock::now() };
		std::this_thread::sleep_for(sleepTime);
	}
}
