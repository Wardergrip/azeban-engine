#pragma once
#include "Singleton.h"
#include <vector>
#include <memory>
#include <unordered_map>
#include "XBoxController.h"
#include "Command.h"

namespace aze
{
	enum class GamepadButton
	{
		DPAD_UP = 0x0001,
		DPAD_DOWN = 0x0002,
		DPAD_LEFT = 0x0004,
		DPAD_RIGHT = 0x0008,
		START = 0x0010,
		BACK = 0x0020,
		LEFT_SHOULDER = 0x0100,
		RIGHT_SHOULDER = 0x0200,
		A = 0x1000,
		B = 0x2000,
		X = 0x4000,
		Y = 0x8000
	};
	enum class GamepadAxis
	{
		LEFT_THUMB = 0x0040,
		RIGHT_THUMB = 0x0080,
		LEFT_SHOULDER = 0x0100,
		RIGHT_SHOULDER = 0x0200
	};

	enum InputType
	{
		OnButtonUp,
		OnButtonDown,
		OnButtonPressed
	};

	struct ControllerKey
	{
		ControllerKey(ControllerIdx idx = -1, ControllerButton cButton = -1, InputType type = InputType::OnButtonDown)
			:controllerIdx{idx}
			,button{ cButton }
			,inputType{type}
		{}
		ControllerIdx controllerIdx{};
		ControllerButton button{};
		InputType inputType{};

		bool operator==(const ControllerKey& other) const
		{
			return
				(
					controllerIdx == other.controllerIdx
					&&
					button == other.button
					&&
					inputType == other.inputType
				);
		}
	};
}

namespace std 
{
	// https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key
	template <>
	struct hash<aze::ControllerKey>
	{
		std::size_t operator()(const aze::ControllerKey& k) const
		{
			using std::hash;

			// Compute individual hash values for first,
			// second and third and combine them using XOR
			// and bit shifting:

			return 
				(
					(hash<unsigned int>()(k.controllerIdx) 
					^ 
					(hash<unsigned int>()(k.button) << 1)) >> 1
					^ 
					(hash<unsigned int>()(k.inputType) << 1)
				);
		}
	};

}

namespace aze
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

		void BindCommand(std::unique_ptr<Command> pCommand, ControllerKey key);

	private:
		using ControllerCommandsMap = std::unordered_map<ControllerKey, std::unique_ptr<Command>>;
		std::vector<std::unique_ptr<XBoxController>> m_pControllers{};
		ControllerCommandsMap m_pControllerKeyCommands{};
	};

}
