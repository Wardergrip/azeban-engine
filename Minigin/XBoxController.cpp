#include "XBoxController.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>

#pragma comment(lib,"xinput.lib")

using namespace aze;

class XBoxController::XBoxControllerImpl final
{
public:
	XBoxControllerImpl(unsigned int controllerIdx);

	void Update();
	bool IsDownThisFrame(unsigned int button) const;
	bool IsUpThisFrame(unsigned int button) const;
	bool IsPressed(unsigned int button) const;

private:
	XINPUT_STATE m_CurrentState{};
	XINPUT_STATE m_PreviousState{};
	XINPUT_KEYSTROKE m_CurrentKeyStroke{};
	unsigned int m_ControllerIndex{};

	unsigned int m_ButtonsPressedThisFrame;
	unsigned int m_ButtonsReleasedThisFrame;
};

XBoxController::XBoxControllerImpl::XBoxControllerImpl(unsigned int controllerIdx)
{
	m_ControllerIndex = controllerIdx;
}

void XBoxController::XBoxControllerImpl::Update()
{
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_ControllerIndex, &m_CurrentState);

	auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
	m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
}

bool XBoxController::XBoxControllerImpl::IsDownThisFrame(unsigned int button) const
{
	return m_ButtonsPressedThisFrame & button;
}

bool XBoxController::XBoxControllerImpl::IsUpThisFrame(unsigned int button) const
{
	return m_ButtonsReleasedThisFrame & button;
}

bool XBoxController::XBoxControllerImpl::IsPressed(unsigned int button) const
{
	return m_CurrentState.Gamepad.wButtons & button;
}

// ===============================================================================

aze::XBoxController::XBoxController(ControllerIdx idx)
{
	pImpl = std::make_unique<XBoxControllerImpl>(idx);
}

aze::XBoxController::~XBoxController() = default;

void aze::XBoxController::Update()
{
	pImpl->Update();
}

bool aze::XBoxController::IsDownThisFrame(ControllerButton button) const
{
	return pImpl->IsDownThisFrame(button);
}

bool aze::XBoxController::IsUpThisFrame(ControllerButton button) const
{
	return pImpl->IsUpThisFrame(button);
}

bool aze::XBoxController::IsPressed(ControllerButton button) const
{
	return pImpl->IsPressed(button);
}
