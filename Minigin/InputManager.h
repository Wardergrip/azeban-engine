#pragma once
#include "Singleton.h"

namespace aze
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
	};

}
