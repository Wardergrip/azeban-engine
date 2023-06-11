#include "PlayerComponent.h"
#include <SceneManager.h>
#include <Scene.h>
#include <iostream>

aze::PlayerComponent::PlayerComponent(GameObject* pParent)
	:Component{ pParent }
	,m_pCurrentState{nullptr}
	,m_IdleState{std::make_unique<IdleState>(this)}
	,m_HurtState{std::make_unique<HurtState>(this)}
	,m_DeadState{std::make_unique<DeadState>(this)}
{
	m_pCurrentState = m_IdleState.get();
}

void aze::PlayerComponent::Update()
{
	if (m_pCurrentState == nullptr)
	{
		std::cout << "Currentstate is nullptr, something went wrong\n";
		return;
	}
	
	auto newState = m_pCurrentState->OnHandle();
	if (newState == m_pCurrentState) return;
	m_pCurrentState->OnExit();
	m_pCurrentState = newState;
	m_pCurrentState->OnEnter();
}
