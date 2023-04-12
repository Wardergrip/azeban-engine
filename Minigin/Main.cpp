#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Azeban.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "TextureObject.h"
#include "GameObject.h"
#include "FPS.h"
#include "RevolutionComponent.h"
#include "RenderComponent.h"
#include "Scene.h"
#include "TrashTheCachPlotterComponent.h"
#include "InputManager.h"
#include <iostream>
#include "DebugCommand.h"
#include "MoveCommand.h"
#include "MovementComponent.h"

void load()
{
	auto& scene = aze::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<aze::GameObject>();
	go->AddComponent<aze::RenderComponent>();
	go->AddComponent<aze::TextureObject>("background.tga");
	scene.Add(go);

	go = std::make_shared<aze::GameObject>();
	go->AddComponent<aze::RenderComponent>();
	go->AddComponent<aze::TextureObject>("logo.tga")/*.lock()->SetPosition(216, 180)*/;
	go->SetPosition(216, 180);
	scene.Add(go);

	auto font = aze::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<aze::GameObject>();
	to->AddComponent<aze::RenderComponent>();
	auto toc = to->AddComponent<aze::TextObject>("Programming 4 Assignment",font);
	//toc.lock()->SetPosition(80, 20);
	to->SetPosition(80, 20);
	scene.Add(to);

	auto fpsFont = aze::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	auto fpsGO = std::make_shared<aze::GameObject>();
	fpsGO->AddComponent<aze::RenderComponent>();
	auto fpsText = fpsGO->AddComponent<aze::TextObject>("FPS",fpsFont);
	fpsText.lock()->/*SetPosition(10, 10).*/SetColor(SDL_Color{255,255,0});
	fpsGO->SetPosition(10, 10);
	auto fps = fpsGO->AddComponent<aze::FPS>(fpsText);
	fps.lock()->SetUpdateInterval(1.f);
	scene.Add(fpsGO);

	auto go_bub = std::make_shared<aze::GameObject>();
	go_bub->SetPosition(100, 100);
	go_bub->AddComponent<aze::RenderComponent>();
	go_bub->AddComponent<aze::TextureObject>("Bub.png");
	auto bubMovement = go_bub->AddComponent<aze::MovementComponent>();
	auto go_bob = std::make_shared<aze::GameObject>();
	go_bob->SetPosition(100, 200);
	go_bob->AddComponent<aze::RenderComponent>();
	go_bob->AddComponent<aze::TextureObject>("Bob.png");
	auto bobMovement = go_bob->AddComponent<aze::MovementComponent>();
	scene.Add(go_bub);
	scene.Add(go_bob);

	// Trash the cache
	/*auto plotter = std::make_shared<aze::GameObject>();
	scene.Add(plotter);
	plotter->AddComponent<aze::TrashTheCachPlotterComponent>();*/

	//aze::InputManager::GetInstance().BindCommand(std::make_unique<aze::DebugCommand>("Test command"), aze::ControllerKey{aze::ControllerIdx{0},static_cast<aze::ControllerButton>(aze::GamepadButton::DPAD_LEFT)});

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

		inputManager.BindCommand(std::make_unique<MoveCommand>(bobMovement, vec2{ 1,0 }, movementSpeed), KeyboardKey{ static_cast<ControllerButton>(SDLK_RIGHT),OnButtonPressed });
		inputManager.BindCommand(std::make_unique<MoveCommand>(bobMovement, vec2{ -1,0 }, movementSpeed), KeyboardKey{ static_cast<ControllerButton>(SDLK_LEFT),OnButtonPressed });
		inputManager.BindCommand(std::make_unique<MoveCommand>(bobMovement, vec2{ 0,-1 }, movementSpeed), KeyboardKey{ static_cast<ControllerButton>(SDLK_UP),OnButtonPressed });
		inputManager.BindCommand(std::make_unique<MoveCommand>(bobMovement, vec2{ 0,1 }, movementSpeed), KeyboardKey{ static_cast<ControllerButton>(SDLK_DOWN),OnButtonPressed });
	}
}

int main(int, char*[]) {
	aze::Azeban engine("../Data/");
	engine.Run(load);
    return 0;
}