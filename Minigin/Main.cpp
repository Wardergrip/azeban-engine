//#include <SDL.h>
//
//#if _DEBUG
//// ReSharper disable once CppUnusedIncludeDirective
//#if __has_include(<vld.h>)
//#include <vld.h>
//#endif
//#endif
//
//#include "Azeban.h"
//#include "SceneManager.h"
//#include "ResourceManager.h"
//#include "TextObject.h"
//#include "TextureObject.h"
//#include "GameObject.h"
//#include "FPS.h"
//#include "RevolutionComponent.h"
//#include "RenderComponent.h"
//#include "Scene.h"
//#include "TrashTheCachPlotterComponent.h"
//#include "InputManager.h"
//#include <iostream>
//#include "DebugCommand.h"
//#include "MoveCommand.h"
//#include "MovementComponent.h"
//#include "LivesDisplayComponent.h"
//#include "LivesComponent.h"
//#include "RemoveLifeCommand.h" 
//#include "ScoreComponent.h"
//#include "AddScoreCommand.h"
//#include "ScoreDisplayComponent.h"
//
//void load()
//{
//	auto& scene = aze::SceneManager::GetInstance().CreateScene("Demo");
//
//	{
//		auto go = std::make_shared<aze::GameObject>();
//		go->AddComponent<aze::RenderComponent>();
//		go->AddComponent<aze::TextureObject>("background.tga");
//		scene.Add(go);
//
//		go = std::make_shared<aze::GameObject>();
//		go->AddComponent<aze::RenderComponent>();
//		go->AddComponent<aze::TextureObject>("logo.tga")/*.lock()->SetPosition(216, 180)*/;
//		go->SetPosition(216, 180);
//		scene.Add(go);
//
//		auto font = aze::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
//		auto to = std::make_shared<aze::GameObject>();
//		to->AddComponent<aze::RenderComponent>();
//		/*auto toc = */to->AddComponent<aze::TextObject>("Programming 4 Assignment", font);
//		//toc->SetPosition(80, 20);
//		to->SetPosition(80, 20);
//		scene.Add(to);
//	}
//
//	auto fpsFont = aze::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
//	auto fpsGO = std::make_shared<aze::GameObject>();
//	fpsGO->AddComponent<aze::RenderComponent>();
//	auto fpsText = fpsGO->AddComponent<aze::TextObject>("FPS",fpsFont);
//	fpsText->/*SetPosition(10, 10).*/SetColor(SDL_Color{255,255,0});
//	fpsGO->SetPosition(10, 10);
//	auto fps = fpsGO->AddComponent<aze::FPS>(fpsText);
//	fps->SetUpdateInterval(1.f);
//	scene.Add(fpsGO);
//
//	auto go_bub = std::make_shared<aze::GameObject>();
//	go_bub->SetPosition(100, 100);
//	go_bub->AddComponent<aze::RenderComponent>();
//	go_bub->AddComponent<aze::TextureObject>("Bub.png");
//	auto bubMovement = go_bub->AddComponent<aze::MovementComponent>();
//	auto bubLives = go_bub->AddComponent<aze::LivesComponent>();
//	auto bubScore = go_bub->AddComponent<aze::ScoreComponent>();
//
//	auto go_bob = std::make_shared<aze::GameObject>();
//	go_bob->SetPosition(100, 200);
//	go_bob->AddComponent<aze::RenderComponent>();
//	go_bob->AddComponent<aze::TextureObject>("Bob.png");
//	auto bobMovement = go_bob->AddComponent<aze::MovementComponent>();
//	auto bobLives = go_bob->AddComponent<aze::LivesComponent>();
//	auto bobScore = go_bob->AddComponent<aze::ScoreComponent>();
//	scene.Add(go_bub);
//	scene.Add(go_bob);
//
//	auto uiFont = aze::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
//
//	auto bub_livesGO = std::make_shared<aze::GameObject>();
//	bub_livesGO->AddComponent<aze::RenderComponent>();
//	auto bub_livesText = bub_livesGO->AddComponent<aze::TextObject>("Lives: " + std::to_string(bubLives->GetLivesAmount()), uiFont);
//	bub_livesText->SetColor(SDL_Color{255,255,0});
//	bub_livesGO->GetTransform().SetPosition(0, 300);
//	auto bub_livesDisplay = bub_livesGO->AddComponent<aze::LivesDisplayComponent>(bub_livesText);
//	bubLives->AddObserver(bub_livesDisplay);
//	scene.Add(bub_livesGO);
//
//	auto bob_livesGO = std::make_shared<aze::GameObject>();
//	bob_livesGO->AddComponent<aze::RenderComponent>();
//	auto bob_livesText = bob_livesGO->AddComponent<aze::TextObject>("Lives: " + std::to_string(bobLives->GetLivesAmount()), uiFont);
//	bob_livesText->SetColor(SDL_Color{ 0,255,0 });
//	bob_livesGO->GetTransform().SetPosition(0, 350);
//	auto bob_livesDisplay = bob_livesGO->AddComponent<aze::LivesDisplayComponent>(bob_livesText);
//	bobLives->AddObserver(bob_livesDisplay);
//	scene.Add(bob_livesGO);
//
//	auto bub_scoreGO = std::make_shared<aze::GameObject>();
//	bub_scoreGO->AddComponent<aze::RenderComponent>();
//	auto bub_scoreText = bub_scoreGO->AddComponent<aze::TextObject>("Score: " + std::to_string(bubScore->GetScoreAmount()), uiFont);
//	bub_scoreText->SetColor(SDL_Color{ 255,255,0 });
//	bub_scoreGO->GetTransform().SetPosition(0, 320);
//	auto bub_scoreDisplay = bub_scoreGO->AddComponent<aze::ScoreDisplayComponent>(bub_scoreText);
//	bubScore->AddObserver(bub_scoreDisplay);
//	scene.Add(bub_scoreGO);
//
//	auto bob_scoreGO = std::make_shared<aze::GameObject>();
//	bob_scoreGO->AddComponent<aze::RenderComponent>();
//	auto bob_scoreText = bob_scoreGO->AddComponent<aze::TextObject>("Score: " + std::to_string(bobScore->GetScoreAmount()), uiFont);
//	bob_scoreText->SetColor(SDL_Color{ 0,255,0 });
//	bob_scoreGO->GetTransform().SetPosition(0, 370);
//	auto bob_scoreDisplay = bob_scoreGO->AddComponent<aze::ScoreDisplayComponent>(bob_scoreText);
//	bobScore->AddObserver(bob_scoreDisplay);
//	scene.Add(bob_scoreGO);
//	
//
//	// Trash the cache
//	/*auto plotter = std::make_shared<aze::GameObject>();
//	scene.Add(plotter);
//	plotter->AddComponent<aze::TrashTheCachPlotterComponent>();*/
//
//	//aze::InputManager::GetInstance().BindCommand(std::make_unique<aze::DebugCommand>("Test command"), aze::ControllerKey{aze::ControllerIdx{0},static_cast<aze::ControllerButton>(aze::GamepadButton::DPAD_LEFT)});
//
//	constexpr float movementSpeed{ 50.f };
//	// Input bindings
//	{
//		using namespace aze;
//		using namespace glm;
//		
//		InputManager& inputManager = InputManager::GetInstance();
//		inputManager.BindCommand(std::make_unique<MoveCommand>(bubMovement, vec2{ 1,0 }, movementSpeed * 2.f), ControllerKey{ ControllerIdx{0},static_cast<ControllerButton>(GamepadButton::DPAD_RIGHT),OnButtonPressed });
//		inputManager.BindCommand(std::make_unique<MoveCommand>(bubMovement, vec2{ -1,0 }, movementSpeed * 2.f), ControllerKey{ ControllerIdx{0},static_cast<ControllerButton>(GamepadButton::DPAD_LEFT),OnButtonPressed });
//		inputManager.BindCommand(std::make_unique<MoveCommand>(bubMovement, vec2{ 0,-1 }, movementSpeed * 2.f), ControllerKey{ ControllerIdx{0},static_cast<ControllerButton>(GamepadButton::DPAD_UP),OnButtonPressed });
//		inputManager.BindCommand(std::make_unique<MoveCommand>(bubMovement, vec2{ 0,1 }, movementSpeed * 2.f), ControllerKey{ ControllerIdx{0},static_cast<ControllerButton>(GamepadButton::DPAD_DOWN),OnButtonPressed });
//
//		inputManager.BindCommand(std::make_unique<RemoveLifeCommand>(bubLives), ControllerKey{ControllerIdx{0},static_cast<ControllerButton>(GamepadButton::A),OnButtonDown});
//		inputManager.BindCommand(std::make_unique<AddScoreCommand>(bubScore), ControllerKey{ControllerIdx{0},static_cast<ControllerButton>(GamepadButton::B),OnButtonDown});
//
//		inputManager.BindCommand(std::make_unique<MoveCommand>(bobMovement, vec2{ 1,0 }, movementSpeed), KeyboardKey{ static_cast<KeyboardButton>(SDLK_RIGHT),OnButtonPressed });
//		inputManager.BindCommand(std::make_unique<MoveCommand>(bobMovement, vec2{ -1,0 }, movementSpeed), KeyboardKey{ static_cast<KeyboardButton>(SDLK_LEFT),OnButtonPressed });
//		inputManager.BindCommand(std::make_unique<MoveCommand>(bobMovement, vec2{ 0,-1 }, movementSpeed), KeyboardKey{ static_cast<KeyboardButton>(SDLK_UP),OnButtonPressed });
//		inputManager.BindCommand(std::make_unique<MoveCommand>(bobMovement, vec2{ 0,1 }, movementSpeed), KeyboardKey{ static_cast<KeyboardButton>(SDLK_DOWN),OnButtonPressed });
//
//		inputManager.BindCommand(std::make_unique<RemoveLifeCommand>(bobLives), KeyboardKey{ static_cast<KeyboardButton>(SDLK_SPACE),OnButtonDown });
//		inputManager.BindCommand(std::make_unique<AddScoreCommand>(bobScore), KeyboardKey{ static_cast<KeyboardButton>(SDLK_v),OnButtonDown });
//
//		std::cout << "[INFO] CONTROLS\n"
//			<< "Player 1:\n"
//			<< "- Dpad: movement\n"
//			<< "- A: remove life\n"
//			<< "- B: add score\n"
//			<< "Player 2:\n"
//			<< "- Arrow keys: movement\n"
//			<< "- Space: remove life\n"
//			<< "- v: add score\n"
//			;
//	}
//}
//
//int main(int, char*[]) 
//{
//	aze::Azeban engine("../Data/");
//	engine.Run(load);
//    return 0;
//}