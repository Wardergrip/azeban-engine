#pragma once
#include <Observer.h>
#include "PlayerState.h"
#include "Ev_PlayerDied.h"

namespace aze
{
	class LivesComponent;

	class IdleState final : public PlayerState, Observer<Ev_PlayerDied>
	{
	public:
		IdleState(PlayerComponent* pPlayerComponent);

		virtual void OnNotify(Ev_PlayerDied* data);
		virtual PlayerState* OnHandle() override;
		virtual void OnExit() override;

	private:
		bool m_IsHurt;
		bool m_IsDead;
	};

	class HurtState final : public PlayerState
	{
	public:
		HurtState(PlayerComponent* pPlayerComponent);

		virtual void OnEnter() override;
		virtual PlayerState* OnHandle() override;
		virtual void OnExit() override;

	private:
		LivesComponent* m_pLivesComponent;
		const float m_Timer;
		float m_ElapsedTime;
	};
	
	class DeadState final : public PlayerState
	{
	public:
		DeadState(PlayerComponent* pPlayerComponent);

		virtual PlayerState* OnHandle() override;

	private:
		bool m_IsLoading;
	};
}