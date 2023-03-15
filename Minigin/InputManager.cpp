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

	return true;
}
