#pragma once
#include <iostream>

#include "SceneManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "FPS.h"

#include "TextObject.h"
#include "TextureObject.h"

#include "Scene.h"
#include "GameObject.h"

#include "DebugCommand.h"
#include "MoveCommand.h"
#include "RemoveLifeCommand.h" 
#include "AddScoreCommand.h"

#include "RevolutionComponent.h"
#include "RenderComponent.h"
#include "MovementComponent.h"
#include "LivesComponent.h"
#include "ScoreComponent.h"
#include "LivesDisplayComponent.h"
#include "ScoreDisplayComponent.h"

using namespace aze;

void DemoScene()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	{
		auto go = std::make_shared<GameObject>();
		go->AddComponent<RenderComponent>();
		go->AddComponent<TextureObject>("background.tga");
		scene.Add(go);

		go = std::make_shared<GameObject>();
		go->AddComponent<RenderComponent>();
		go->AddComponent<TextureObject>("logo.tga")/*->SetPosition(216, 180)*/;
		go->SetPosition(216, 180);
		scene.Add(go);

		auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
		auto to = std::make_shared<GameObject>();
		to->AddComponent<RenderComponent>();
		to->AddComponent<TextObject>("Programming 4 Assignment", font);
		to->SetPosition(80, 20);
		scene.Add(to);
	}

	auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	auto fpsGO = std::make_shared<GameObject>();
	fpsGO->AddComponent<RenderComponent>();
	auto fpsText = fpsGO->AddComponent<TextObject>("FPS", fpsFont);
	fpsText->SetColor(SDL_Color{ 255,255,0 });
	fpsGO->SetPosition(10, 10);
	auto fps = fpsGO->AddComponent<FPS>(fpsText);
	fps->SetUpdateInterval(1.f);
	scene.Add(fpsGO);

	auto go_bub = std::make_shared<GameObject>();
	go_bub->SetPosition(100, 100);
	go_bub->AddComponent<RenderComponent>();
	go_bub->AddComponent<TextureObject>("Bub.png");
	auto bubMovement = go_bub->AddComponent<MovementComponent>();
	auto bubLives = go_bub->AddComponent<LivesComponent>();
	auto bubScore = go_bub->AddComponent<ScoreComponent>();

	auto go_bob = std::make_shared<GameObject>();
	go_bob->SetPosition(100, 200);
	go_bob->AddComponent<RenderComponent>();
	go_bob->AddComponent<TextureObject>("Bob.png");
	auto bobMovement = go_bob->AddComponent<MovementComponent>();
	auto bobLives = go_bob->AddComponent<LivesComponent>();
	auto bobScore = go_bob->AddComponent<ScoreComponent>();
	scene.Add(go_bub);
	scene.Add(go_bob);

	auto uiFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);

	auto bub_livesGO = std::make_shared<GameObject>();
	bub_livesGO->AddComponent<RenderComponent>();
	auto bub_livesText = bub_livesGO->AddComponent<TextObject>("Lives: " + std::to_string(bubLives->GetLivesAmount()), uiFont);
	bub_livesText->SetColor(SDL_Color{ 255,255,0 });
	bub_livesGO->GetTransform().SetPosition(0, 300);
	auto bub_livesDisplay = bub_livesGO->AddComponent<LivesDisplayComponent>(bub_livesText);
	bubLives->AddObserver(bub_livesDisplay);
	scene.Add(bub_livesGO);

	auto bob_livesGO = std::make_shared<GameObject>();
	bob_livesGO->AddComponent<RenderComponent>();
	auto bob_livesText = bob_livesGO->AddComponent<TextObject>("Lives: " + std::to_string(bobLives->GetLivesAmount()), uiFont);
	bob_livesText->SetColor(SDL_Color{ 0,255,0 });
	bob_livesGO->GetTransform().SetPosition(0, 350);
	auto bob_livesDisplay = bob_livesGO->AddComponent<LivesDisplayComponent>(bob_livesText);
	bobLives->AddObserver(bob_livesDisplay);
	scene.Add(bob_livesGO);

	auto bub_scoreGO = std::make_shared<GameObject>();
	bub_scoreGO->AddComponent<RenderComponent>();
	auto bub_scoreText = bub_scoreGO->AddComponent<TextObject>("Score: " + std::to_string(bubScore->GetScoreAmount()), uiFont);
	bub_scoreText->SetColor(SDL_Color{ 255,255,0 });
	bub_scoreGO->GetTransform().SetPosition(0, 320);
	auto bub_scoreDisplay = bub_scoreGO->AddComponent<ScoreDisplayComponent>(bub_scoreText);
	bubScore->AddObserver(bub_scoreDisplay);
	scene.Add(bub_scoreGO);

	auto bob_scoreGO = std::make_shared<GameObject>();
	bob_scoreGO->AddComponent<RenderComponent>();
	auto bob_scoreText = bob_scoreGO->AddComponent<TextObject>("Score: " + std::to_string(bobScore->GetScoreAmount()), uiFont);
	bob_scoreText->SetColor(SDL_Color{ 0,255,0 });
	bob_scoreGO->GetTransform().SetPosition(0, 370);
	auto bob_scoreDisplay = bob_scoreGO->AddComponent<ScoreDisplayComponent>(bob_scoreText);
	bobScore->AddObserver(bob_scoreDisplay);
	scene.Add(bob_scoreGO);

	constexpr float movementSpeed{ 50.f };
	// Input bindings
	{
		using namespace aze;
		using namespace glm;

		InputManager& inputManager = InputManager::GetInstance();
		inputManager.BindCommand(std::make_unique<MoveCommand>(bubMovement, vec2{ 1,0 }, movementSpeed * 2.f), ControllerKey{ ControllerIdx{0},static_cast<ControllerButton>(GamepadButton::DPAD_RIGHT),OnButtonPressed });
		inputManager.BindCommand(std::make_unique<MoveCommand>(bubMovement, vec2{ -1,0 }, movementSpeed * 2.f), ControllerKey{ ControllerIdx{0},static_cast<ControllerButton>(GamepadButton::DPAD_LEFT),OnButtonPressed });
		inputManager.BindCommand(std::make_unique<MoveCommand>(bubMovement, vec2{ 0,-1 }, movementSpeed * 2.f), ControllerKey{ ControllerIdx{0},static_cast<ControllerButton>(GamepadButton::DPAD_UP),OnButtonPressed });
		inputManager.BindCommand(std::make_unique<MoveCommand>(bubMovement, vec2{ 0,1 }, movementSpeed * 2.f), ControllerKey{ ControllerIdx{0},static_cast<ControllerButton>(GamepadButton::DPAD_DOWN),OnButtonPressed });

		inputManager.BindCommand(std::make_unique<RemoveLifeCommand>(bubLives), ControllerKey{ ControllerIdx{0},static_cast<ControllerButton>(GamepadButton::A),OnButtonDown });
		inputManager.BindCommand(std::make_unique<AddScoreCommand>(bubScore), ControllerKey{ ControllerIdx{0},static_cast<ControllerButton>(GamepadButton::B),OnButtonDown });

		inputManager.BindCommand(std::make_unique<MoveCommand>(bobMovement, vec2{ 1,0 }, movementSpeed), KeyboardKey{ static_cast<KeyboardButton>(SDLK_RIGHT),OnButtonPressed });
		inputManager.BindCommand(std::make_unique<MoveCommand>(bobMovement, vec2{ -1,0 }, movementSpeed), KeyboardKey{ static_cast<KeyboardButton>(SDLK_LEFT),OnButtonPressed });
		inputManager.BindCommand(std::make_unique<MoveCommand>(bobMovement, vec2{ 0,-1 }, movementSpeed), KeyboardKey{ static_cast<KeyboardButton>(SDLK_UP),OnButtonPressed });
		inputManager.BindCommand(std::make_unique<MoveCommand>(bobMovement, vec2{ 0,1 }, movementSpeed), KeyboardKey{ static_cast<KeyboardButton>(SDLK_DOWN),OnButtonPressed });

		inputManager.BindCommand(std::make_unique<RemoveLifeCommand>(bobLives), KeyboardKey{ static_cast<KeyboardButton>(SDLK_SPACE),OnButtonDown });
		inputManager.BindCommand(std::make_unique<AddScoreCommand>(bobScore), KeyboardKey{ static_cast<KeyboardButton>(SDLK_v),OnButtonDown });

		std::cout << "[INFO] CONTROLS\n"
			<< "Player 1:\n"
			<< "- Dpad: movement\n"
			<< "- A: remove life\n"
			<< "- B: add score\n"
			<< "Player 2:\n"
			<< "- Arrow keys: movement\n"
			<< "- Space: remove life\n"
			<< "- v: add score\n"
			;
	}
}

void LevelOne()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Level 1");

	// FPS
	{
		auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
		auto fpsObj = std::make_shared<GameObject>();
		fpsObj->AddComponent<RenderComponent>();
		auto fpsText = fpsObj->AddComponent<TextObject>("FPS", fpsFont);
		fpsText->SetColor(SDL_Color{ 255,255,0 });
		fpsObj->SetPosition(10, 10);
		auto fps = fpsObj->AddComponent<FPS>(fpsText);
		fps->SetUpdateInterval(1.f);
		scene.Add(fpsObj);
	}

	// Bub
	auto bubObj = std::make_shared<GameObject>();
	bubObj->SetPosition(100, 100);
	bubObj->AddComponent<RenderComponent>();
	bubObj->AddComponent<TextureObject>("Bub.png");
	auto bubMovement = bubObj->AddComponent<MovementComponent>();
	auto bubLives = bubObj->AddComponent<LivesComponent>();
	auto bubScore = bubObj->AddComponent<ScoreComponent>();
	scene.Add(bubObj);

	// Bob
	auto bobObj = std::make_shared<GameObject>();
	bobObj->SetPosition(100, 200);
	bobObj->AddComponent<RenderComponent>();
	bobObj->AddComponent<TextureObject>("Bob.png");
	auto bobMovement = bobObj->AddComponent<MovementComponent>();
	auto bobLives = bobObj->AddComponent<LivesComponent>();
	auto bobScore = bobObj->AddComponent<ScoreComponent>();
	scene.Add(bobObj);

	// Input bindings
	{
		constexpr float movementSpeed{ 50.f };
		using namespace aze;
		using namespace glm;

		InputManager& inputManager = InputManager::GetInstance();
		inputManager.BindCommand(std::make_unique<MoveCommand>(bubMovement, vec2{ 1,0 }, movementSpeed * 2.f), ControllerKey{ ControllerIdx{0},static_cast<ControllerButton>(GamepadButton::DPAD_RIGHT),OnButtonPressed });
		inputManager.BindCommand(std::make_unique<MoveCommand>(bubMovement, vec2{ -1,0 }, movementSpeed * 2.f), ControllerKey{ ControllerIdx{0},static_cast<ControllerButton>(GamepadButton::DPAD_LEFT),OnButtonPressed });
		inputManager.BindCommand(std::make_unique<MoveCommand>(bubMovement, vec2{ 0,-1 }, movementSpeed * 2.f), ControllerKey{ ControllerIdx{0},static_cast<ControllerButton>(GamepadButton::DPAD_UP),OnButtonPressed });
		inputManager.BindCommand(std::make_unique<MoveCommand>(bubMovement, vec2{ 0,1 }, movementSpeed * 2.f), ControllerKey{ ControllerIdx{0},static_cast<ControllerButton>(GamepadButton::DPAD_DOWN),OnButtonPressed });

		inputManager.BindCommand(std::make_unique<RemoveLifeCommand>(bubLives), ControllerKey{ ControllerIdx{0},static_cast<ControllerButton>(GamepadButton::A),OnButtonDown });
		inputManager.BindCommand(std::make_unique<AddScoreCommand>(bubScore), ControllerKey{ ControllerIdx{0},static_cast<ControllerButton>(GamepadButton::B),OnButtonDown });

		inputManager.BindCommand(std::make_unique<MoveCommand>(bobMovement, vec2{ 1,0 }, movementSpeed), KeyboardKey{ static_cast<KeyboardButton>(SDLK_RIGHT),OnButtonPressed });
		inputManager.BindCommand(std::make_unique<MoveCommand>(bobMovement, vec2{ -1,0 }, movementSpeed), KeyboardKey{ static_cast<KeyboardButton>(SDLK_LEFT),OnButtonPressed });
		inputManager.BindCommand(std::make_unique<MoveCommand>(bobMovement, vec2{ 0,-1 }, movementSpeed), KeyboardKey{ static_cast<KeyboardButton>(SDLK_UP),OnButtonPressed });
		inputManager.BindCommand(std::make_unique<MoveCommand>(bobMovement, vec2{ 0,1 }, movementSpeed), KeyboardKey{ static_cast<KeyboardButton>(SDLK_DOWN),OnButtonPressed });

		inputManager.BindCommand(std::make_unique<RemoveLifeCommand>(bobLives), KeyboardKey{ static_cast<KeyboardButton>(SDLK_SPACE),OnButtonDown });
		inputManager.BindCommand(std::make_unique<AddScoreCommand>(bobScore), KeyboardKey{ static_cast<KeyboardButton>(SDLK_v),OnButtonDown });

		std::cout << "[INFO] CONTROLS\n"
			<< "Player 1:\n"
			<< "- Dpad: movement\n"
			<< "- A: remove life\n"
			<< "- B: add score\n"
			<< "Player 2:\n"
			<< "- Arrow keys: movement\n"
			<< "- Space: remove life\n"
			<< "- v: add score\n"
			;
	}
}

void full_load()
{
	//DemoScene();
	LevelOne();
}