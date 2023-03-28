#include <SDL.h>
#include "InputManager.h"
#include "../3rdParty/imgui/imgui_impl_sdl2.h"

bool aze::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		// etc...
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	for (const auto& pController : m_pControllers)
	{
		pController->Update();
	}

	for (const auto& pControllerKeyCommand : m_pControllerKeyCommands)
	{
		const auto& [key, command] = pControllerKeyCommand;

		bool execute{ false };
		switch (key.inputType)
		{
		case InputType::OnButtonUp:
			execute = m_pControllers[key.controllerIdx]->IsUpThisFrame(key.button);
			break;
		case InputType::OnButtonDown:
			execute = m_pControllers[key.controllerIdx]->IsDownThisFrame(key.button);
			break;
		case InputType::OnButtonPressed:
			execute = m_pControllers[key.controllerIdx]->IsPressed(key.button);
			break;
		}

		if (execute)
		{
			command->Execute();
		}
	}

	return true;
}

void aze::InputManager::BindCommand(std::unique_ptr<Command> pCommand, ControllerKey key)
{
	if (key.controllerIdx >= m_pControllers.size())
	{
		m_pControllers.push_back(std::make_unique<XBoxController>(key.controllerIdx));
	}

	m_pControllerKeyCommands[key] = std::move(pCommand);
}
