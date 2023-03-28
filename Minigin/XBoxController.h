#pragma once
#include <memory>

namespace aze
{
	using ControllerButton = unsigned int;
	using ControllerIdx = unsigned int;
	class XBoxController final
	{
	public:
		XBoxController(ControllerIdx idx);
		~XBoxController();

		void Update();
		bool IsDownThisFrame(ControllerButton button) const;
		bool IsUpThisFrame(ControllerButton button) const;
		bool IsPressed(ControllerButton button) const;
	private:
		class XBoxControllerImpl;
		std::unique_ptr<XBoxControllerImpl> pImpl;
	};
}

