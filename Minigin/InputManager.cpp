#include <SDL.h>
#include "InputManager.h"
#include "../3rdParty/imgui/imgui_impl_sdl2.h"

bool aze::InputManager::ProcessInput()
{
	m_KeyboardDownInputs.clear();
	m_KeyboardUpInputs.clear();
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}

		// find the key in our currently being pressed buffer
		const auto it{ m_KeyboardPressedInputs.find(e.key.keysym.sym) };
		switch (e.key.type)
		{
		case SDL_KEYDOWN:
			// If we don't find the keypress
			if (it == m_KeyboardPressedInputs.end())
			{
				// Add it to the buffers
				m_KeyboardPressedInputs.insert(e.key.keysym.sym);
				m_KeyboardDownInputs.insert(e.key.keysym.sym);
			}
			break;
		case SDL_KEYUP:
			// If we find the keypress
			if (it != m_KeyboardPressedInputs.end())
			{
				// Remove it from our being pressed buffer
				// Add it to our up buffer
				m_KeyboardPressedInputs.erase(it);
				m_KeyboardUpInputs.insert(e.key.keysym.sym);
			}
			break;
		}

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

	for (const auto& pKeyboardKeyCommand : m_pKeyboardKeyCommands)
	{
		const auto& [key, command] = pKeyboardKeyCommand;

		switch (key.inputType)
		{
		case InputType::OnButtonUp:
			if (m_KeyboardUpInputs.contains(key.button))
			{
				command->Execute();
			}
			break;
		case InputType::OnButtonDown:
			if (m_KeyboardDownInputs.contains(key.button))
			{
				command->Execute();
			}
			break;
		case InputType::OnButtonPressed:
			if (m_KeyboardPressedInputs.contains(key.button))
			{
				command->Execute();
			}
			break;
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

void aze::InputManager::BindCommand(std::unique_ptr<Command> pCommand, KeyboardKey key)
{
	m_pKeyboardKeyCommands[key] = std::move(pCommand);
}
