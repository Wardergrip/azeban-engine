#include "PlayerStates.h"
#include <GameObject.h>
#include <GameTime.h>
#include "PlayerComponent.h"
#include "LivesComponent.h"
#include "GameManager.h"
#include <SceneManager.h>
#include <iostream>

// IDLE
aze::IdleState::IdleState(PlayerComponent* pPlayerComponent)
	:PlayerState(pPlayerComponent)
	,m_IsDead{false}
	,m_IsHurt{false}
{
	pPlayerComponent->GetGameObject()->GetComponent<LivesComponent>()->AddObserver(this);
}

void aze::IdleState::OnNotify(Ev_PlayerDied* data)
{
	if (data->GetLivesLeft() > 0)
	{
		auto lives = data->GetPlayer()->GetComponent<LivesComponent>();
		if (lives) lives->SetIsInvincible(true);
		m_IsHurt = true;
	}
	else m_IsDead = true;
}

aze::PlayerState* aze::IdleState::OnHandle()
{
	if (m_IsDead)
	{
		return m_pPlayerComponent->GetDeadState();
	}
	if (m_IsHurt)
	{
		return m_pPlayerComponent->GetHurtState();
	}
	return this;
}

void aze::IdleState::OnExit()
{
	m_IsHurt = false;
	m_IsDead = false;
}

// HURT
aze::HurtState::HurtState(PlayerComponent* pPlayerComponent)
	:PlayerState{pPlayerComponent}
	,m_Timer{3.f}
	,m_ElapsedTime{0.f}
	,m_pLivesComponent{pPlayerComponent->GetGameObject()->GetComponent<LivesComponent>()}
{
}

void aze::HurtState::OnEnter()
{
	m_pLivesComponent->SetIsInvincible(true);
}

aze::PlayerState* aze::HurtState::OnHandle()
{
	static auto& gameTime{ GameTime::GetInstance() };
	m_ElapsedTime += gameTime.GetElapsed();
	if (m_ElapsedTime >= m_Timer)
	{
		return m_pPlayerComponent->GetIdleState();
	}
	return this;
}

void aze::HurtState::OnExit()
{
	m_pLivesComponent->SetIsInvincible(false);
	m_ElapsedTime = 0.0f;
}

// DEAD
aze::DeadState::DeadState(PlayerComponent* pPlayerComponent)
	:PlayerState{pPlayerComponent}
	,m_IsLoading{false}
{
}

aze::PlayerState* aze::DeadState::OnHandle()
{
	if (!m_IsLoading)
	{
		m_IsLoading = true;
		SceneManager::GetInstance().SetActiveScene("MainMenu");
	}
	return this;
}
