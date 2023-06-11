#include "SceneDefinitions.h"

// Managers / essentials
#include <iostream>
#include "InputManager.h"
#include "ResourceManager.h"
#include "ServiceManager.h"
#include "FPS.h"
#include "GameManager.h"

// Services
#include "SoundSystemLogger.h"
#include "SDLSoundSystem.h"

// Data
#include "TextObject.h"
#include "TextureObject.h"

#include "ImageParser.h"

// Structural
#include "Scene.h"
#include "GameObject.h"

// Commands
#include "DebugCommand.h"
#include "MoveCommand.h"
#include "RemoveLifeCommand.h" 
#include "AddScoreCommand.h"
#include "AudioPlayCommand.h"
#include "MuteCommand.h"
#include "JumpCommand.h"

// Components
#include "RevolutionComponent.h"
#include "RenderComponent.h"
#include "MovementComponent.h"
#include "LivesComponent.h"
#include "ScoreComponent.h"
#include "LivesDisplayComponent.h"
#include "ScoreDisplayComponent.h"
#include "LevelComponent.h"
#include "MainMenuGUIComponent.h"
#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"
#include "LandOnPlatformComponent.h"
#include "EnemyMovementComponent.h"

#include "ColliderLayers.h"

using namespace aze;
using namespace glm;

void aze::DemoScene(Scene& scene)
{
	{
		auto go = new GameObject(&scene);
		go->AddComponent<RenderComponent>();
		go->AddComponent<TextureObject>("background.tga");
		scene.Adopt(go);

		go = new GameObject(&scene);
		go->AddComponent<RenderComponent>();
		go->AddComponent<TextureObject>("logo.tga")/*->SetPosition(216, 180)*/;
		go->SetPosition(216, 180);
		scene.Adopt(go);

		auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
		auto to = new GameObject(&scene);
		to->AddComponent<RenderComponent>();
		to->AddComponent<TextObject>("Programming 4 Assignment", font);
		to->SetPosition(80, 20);
		scene.Adopt(to);
	}

	auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	auto fpsGO = new GameObject(&scene);
	fpsGO->AddComponent<RenderComponent>();
	auto fpsText = fpsGO->AddComponent<TextObject>("FPS", fpsFont);
	fpsText->SetColor(SDL_Color{ 255,255,0 });
	fpsGO->SetPosition(10, 10);
	auto fps = fpsGO->AddComponent<FPS>(fpsText);
	fps->SetUpdateInterval(1.f);
	scene.Adopt(fpsGO);

	auto go_bub = new GameObject(&scene);
	go_bub->SetPosition(100, 100);
	go_bub->AddComponent<RenderComponent>();
	go_bub->AddComponent<TextureObject>("Bub.png");
	auto bubMovement = go_bub->AddComponent<MovementComponent>();
	auto bubLives = go_bub->AddComponent<LivesComponent>();
	auto bubScore = go_bub->AddComponent<ScoreComponent>();

	auto go_bob = new GameObject(&scene);
	go_bob->SetPosition(100, 200);
	go_bob->AddComponent<RenderComponent>();
	go_bob->AddComponent<TextureObject>("Bob.png");
	auto bobMovement = go_bob->AddComponent<MovementComponent>();
	auto bobLives = go_bob->AddComponent<LivesComponent>();
	auto bobScore = go_bob->AddComponent<ScoreComponent>();
	scene.Adopt(go_bub);
	scene.Adopt(go_bob);

	auto uiFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);

	auto bub_livesGO = new GameObject(&scene);
	bub_livesGO->AddComponent<RenderComponent>();
	auto bub_livesText = bub_livesGO->AddComponent<TextObject>("Lives: " + std::to_string(bubLives->GetLivesAmount()), uiFont);
	bub_livesText->SetColor(SDL_Color{ 255,255,0 });
	bub_livesGO->GetTransform().SetPosition(0, 300);
	auto bub_livesDisplay = bub_livesGO->AddComponent<LivesDisplayComponent>(bub_livesText);
	bubLives->AddObserver(bub_livesDisplay);
	scene.Adopt(bub_livesGO);

	auto bob_livesGO = new GameObject(&scene);
	bob_livesGO->AddComponent<RenderComponent>();
	auto bob_livesText = bob_livesGO->AddComponent<TextObject>("Lives: " + std::to_string(bobLives->GetLivesAmount()), uiFont);
	bob_livesText->SetColor(SDL_Color{ 0,255,0 });
	bob_livesGO->GetTransform().SetPosition(0, 350);
	auto bob_livesDisplay = bob_livesGO->AddComponent<LivesDisplayComponent>(bob_livesText);
	bobLives->AddObserver(bob_livesDisplay);
	scene.Adopt(bob_livesGO);

	auto bub_scoreGO = new GameObject(&scene);
	bub_scoreGO->AddComponent<RenderComponent>();
	auto bub_scoreText = bub_scoreGO->AddComponent<TextObject>("Score: " + std::to_string(bubScore->GetScoreAmount()), uiFont);
	bub_scoreText->SetColor(SDL_Color{ 255,255,0 });
	bub_scoreGO->GetTransform().SetPosition(0, 320);
	auto bub_scoreDisplay = bub_scoreGO->AddComponent<ScoreDisplayComponent>(bub_scoreText);
	bubScore->AddObserver(bub_scoreDisplay);
	scene.Adopt(bub_scoreGO);

	auto bob_scoreGO = new GameObject(&scene);
	bob_scoreGO->AddComponent<RenderComponent>();
	auto bob_scoreText = bob_scoreGO->AddComponent<TextObject>("Score: " + std::to_string(bobScore->GetScoreAmount()), uiFont);
	bob_scoreText->SetColor(SDL_Color{ 0,255,0 });
	bob_scoreGO->GetTransform().SetPosition(0, 370);
	auto bob_scoreDisplay = bob_scoreGO->AddComponent<ScoreDisplayComponent>(bob_scoreText);
	bobScore->AddObserver(bob_scoreDisplay);
	scene.Adopt(bob_scoreGO);

	constexpr float movementSpeed{ 50.f };
	// Input bindings
	{
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

void aze::LevelOne(Scene& scene)
{
	// Audio
#if _DEBUG
	ServiceManager::GetInstance().RegisterSoundSystem(std::make_unique<SoundSystemLogger>(std::make_unique<SDLSoundSystem>()));
#else
	ServiceManager::GetInstance().RegisterSoundSystem(std::make_unique<SDLSoundSystem>());
#endif

	// FPS
	{
		auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
		auto fpsObj = new GameObject(&scene);
		fpsObj->AddComponent<RenderComponent>();
		auto fpsText = fpsObj->AddComponent<TextObject>("FPS", fpsFont);
		fpsText->SetColor(SDL_Color{ 255,255,0 });
		fpsObj->SetPosition(10, 10);
		auto fps = fpsObj->AddComponent<FPS>(fpsText);
		fps->SetUpdateInterval(1.f);
		scene.Adopt(fpsObj);
	}

	// Level
	{
		auto levelObj = new GameObject(&scene);
		scene.Adopt(levelObj);

		ImageParser imageParser{ "Level1.png" };
		levelObj->AddComponent<LevelComponent>(&imageParser);
	}

	// Input/controls
	constexpr float movementSpeed{ 50.f };
	constexpr float jumpForce{ 10.0f };

	InputManager& inputManager = InputManager::GetInstance();

	// Players
	GameObject* bobObj{ nullptr };
	GameObject* bubObj{ nullptr };
	auto playerMode = GameManager::GetInstance().GetPlayerMode();
	switch (playerMode)
	{
	case PlayerMode::singlePlayer:
		break;
	case PlayerMode::coop:
	case PlayerMode::versus:
		bubObj = scene.CreateGameObject();
		GameManager::GetInstance().SetBubPlayer(bubObj);
		break;
	}

	// Bub
	if (bubObj)
	{
		auto bubSpawnPoint = GameManager::GetInstance().GetBubSpawnPoint();
		if (bubSpawnPoint)
		{
			const auto& pos = bubSpawnPoint->GetTransform().GetWorldPosition();
			bubObj->SetPosition(pos.x, pos.y);
		}
		else bubObj->SetPosition(100, 200);
		bubObj->AddComponent<RenderComponent>();
		bubObj->AddComponent<TextureObject>("Bub.png");
		auto bubMovement = bubObj->AddComponent<MovementComponent>();
		bubObj->AddComponent<LivesComponent>();
		bubObj->AddComponent<ScoreComponent>();
		auto bubBoxColl = bubObj->AddComponent<BoxColliderComponent>(32.f, 32.f);
		bubBoxColl->SetLayer(layers::L_PLAYER);
		bubBoxColl->RemoveLayerFromMask(layers::L_PLAYER);
		auto bubRigidBody = bubObj->AddComponent<RigidbodyComponent>();
		bubObj->AddComponent<LandOnPlatformComponent>(bubBoxColl, bubRigidBody);

		// Bub Input
		inputManager.BindCommand(std::make_unique<MoveCommand>(bubMovement, vec2{ 1,0 }, movementSpeed), ControllerKey{ ControllerIdx{0},static_cast<ControllerButton>(GamepadButton::DPAD_RIGHT),OnButtonPressed });
		inputManager.BindCommand(std::make_unique<MoveCommand>(bubMovement, vec2{ -1,0 }, movementSpeed), ControllerKey{ ControllerIdx{0},static_cast<ControllerButton>(GamepadButton::DPAD_LEFT),OnButtonPressed });
		inputManager.BindCommand(std::make_unique<JumpCommand>(bubRigidBody, jumpForce), ControllerKey{ ControllerIdx{0},static_cast<ControllerButton>(GamepadButton::DPAD_UP),OnButtonPressed });
	}

	// Bob
	bobObj = scene.CreateGameObject();
	GameManager::GetInstance().SetBobPlayer(bobObj);
	auto bobSpawnPoint = GameManager::GetInstance().GetBobSpawnPoint();
	if (bobSpawnPoint)
	{
		const auto& pos = bobSpawnPoint->GetTransform().GetWorldPosition();
		bobObj->SetPosition(pos.x,pos.y);
	}
	else bobObj->SetPosition(100, 200);
	bobObj->AddComponent<RenderComponent>();
	bobObj->AddComponent<TextureObject>("Bob.png");
	auto bobMovement = bobObj->AddComponent<MovementComponent>();
	bobObj->AddComponent<LivesComponent>();
	bobObj->AddComponent<ScoreComponent>();
	auto bobBoxColl = bobObj->AddComponent<BoxColliderComponent>(32.f, 32.f);
	bobBoxColl->SetLayer(layers::L_PLAYER);
	bobBoxColl->RemoveLayerFromMask(layers::L_PLAYER);
	auto bobRigidBody = bobObj->AddComponent<RigidbodyComponent>();
	bobObj->AddComponent<LandOnPlatformComponent>(bobBoxColl,bobRigidBody);

	// Bob input
	inputManager.BindCommand(std::make_unique<MoveCommand>(bobMovement, vec2{ 1,0 }, movementSpeed), KeyboardKey{ static_cast<KeyboardButton>(SDLK_RIGHT),OnButtonPressed });
	inputManager.BindCommand(std::make_unique<MoveCommand>(bobMovement, vec2{ -1,0 }, movementSpeed), KeyboardKey{ static_cast<KeyboardButton>(SDLK_LEFT),OnButtonPressed });
	inputManager.BindCommand(std::make_unique<JumpCommand>(bobRigidBody, jumpForce), KeyboardKey{ static_cast<KeyboardButton>(SDLK_UP),OnButtonPressed });

	if (bubObj == nullptr)
	{
		// If we are alone, bind controller commands aswell
		inputManager.BindCommand(std::make_unique<MoveCommand>(bobMovement, vec2{ 1,0 }, movementSpeed), ControllerKey{ ControllerIdx{0},static_cast<ControllerButton>(GamepadButton::DPAD_RIGHT),OnButtonPressed });
		inputManager.BindCommand(std::make_unique<MoveCommand>(bobMovement, vec2{ -1,0 }, movementSpeed), ControllerKey{ ControllerIdx{0},static_cast<ControllerButton>(GamepadButton::DPAD_LEFT),OnButtonPressed });
		inputManager.BindCommand(std::make_unique<JumpCommand>(bobRigidBody, jumpForce), ControllerKey{ ControllerIdx{0},static_cast<ControllerButton>(GamepadButton::DPAD_UP),OnButtonPressed });
	}

	// Enemies
	constexpr float enemySpeed{ 30.f };
	for (auto enemySpawnPoint : GameManager::GetInstance().GetEnemySpawnpoints())
	{
		auto enemyObj = scene.CreateGameObject();
		const auto& pos = enemySpawnPoint->GetTransform().GetWorldPosition();
		enemyObj->SetPosition(pos.x, pos.y);
		enemyObj->AddComponent<RenderComponent>();
		enemyObj->AddComponent<TextureObject>("Zen-Chan.png");
		auto movement = enemyObj->AddComponent<MovementComponent>();
		auto coll = enemyObj->AddComponent<BoxColliderComponent>(32.f, 32.f);
		coll->SetIsTrigger(true);
		coll->SetLayer(0x0000);
		auto rb = enemyObj->AddComponent<RigidbodyComponent>();
		enemyObj->AddComponent<LandOnPlatformComponent>(coll, rb);
		enemyObj->AddComponent<EnemyMovementComponent>(movement, enemySpeed);
	}

	// General input
	inputManager.BindCommand(std::make_unique<MuteCommand>(&ServiceManager::GetInstance().GetSoundSystem()), KeyboardKey{ static_cast<KeyboardButton>(SDLK_m),OnButtonDown });

	// Controlls info
	std::cout << "[INFO] CONTROLS\n"
		<< "Player 1:\n"
		<< "- Dpad: movement\n"
		<< "Player 2:\n"
		<< "- Arrow keys: movement\n"
		<< "Misc:\n"
		<< "- m: toggle mute sound\n"
		<< "Note:\n"
		<< "Logging of the sound system will automatically happen in debug\n"
		;
}

void aze::MainMenu(Scene& scene)
{
	auto backGround_go = scene.CreateGameObject();
	backGround_go->AddComponent<RenderComponent>();
	backGround_go->AddComponent<TextureObject>("titlescreen.png");
	backGround_go->SetPosition(130.f, 130.f);

	scene.CreateGameObject()->AddComponent<MainMenuGUIComponent>();
}

void aze::TestScene(Scene& scene)
{
	auto first_go = scene.CreateGameObject();
	first_go->AddComponent<RenderComponent>();
	first_go->AddComponent<TextureObject>("Small.png");
	first_go->AddComponent<BoxColliderComponent>(24.f,24.f);
	auto firstMovementComp = first_go->AddComponent<MovementComponent>();
	first_go->SetPosition(100, 100);

	auto second_go = scene.CreateGameObject();
	second_go->AddComponent<RenderComponent>();
	second_go->AddComponent<TextureObject>("Small.png");
	second_go->AddComponent<BoxColliderComponent>(24.f, 24.f);
	auto secondMovementComp = second_go->AddComponent<MovementComponent>();
	second_go->SetPosition(0, 0);

	// Input
	{
		constexpr float movementSpeed{ 50.f };
		auto& inputManager = InputManager::GetInstance();

		inputManager.BindCommand(std::make_unique<MoveCommand>(firstMovementComp, vec2{ 1,0 }, movementSpeed), KeyboardKey{ static_cast<KeyboardButton>(SDLK_RIGHT),OnButtonPressed });
		inputManager.BindCommand(std::make_unique<MoveCommand>(firstMovementComp, vec2{ -1,0 }, movementSpeed), KeyboardKey{ static_cast<KeyboardButton>(SDLK_LEFT),OnButtonPressed });
		inputManager.BindCommand(std::make_unique<MoveCommand>(firstMovementComp, vec2{ 0,-1 }, movementSpeed), KeyboardKey{ static_cast<KeyboardButton>(SDLK_UP),OnButtonPressed });
		inputManager.BindCommand(std::make_unique<MoveCommand>(firstMovementComp, vec2{ 0,1 }, movementSpeed), KeyboardKey{ static_cast<KeyboardButton>(SDLK_DOWN),OnButtonPressed });

		inputManager.BindCommand(std::make_unique<MoveCommand>(secondMovementComp, vec2{ 1,0 }, movementSpeed), KeyboardKey{ static_cast<KeyboardButton>(SDLK_d),OnButtonPressed });
		inputManager.BindCommand(std::make_unique<MoveCommand>(secondMovementComp, vec2{ -1,0 }, movementSpeed), KeyboardKey{ static_cast<KeyboardButton>(SDLK_a),OnButtonPressed });
		inputManager.BindCommand(std::make_unique<MoveCommand>(secondMovementComp, vec2{ 0,-1 }, movementSpeed), KeyboardKey{ static_cast<KeyboardButton>(SDLK_w),OnButtonPressed });
		inputManager.BindCommand(std::make_unique<MoveCommand>(secondMovementComp, vec2{ 0,1 }, movementSpeed), KeyboardKey{ static_cast<KeyboardButton>(SDLK_s),OnButtonPressed });
	}
}