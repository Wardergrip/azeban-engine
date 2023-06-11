#pragma once
#include <Component.h>
#include <memory>
#include "PlayerStates.h"

namespace aze
{
	class PlayerComponent final : public Component
	{
	public:
		PlayerComponent(GameObject* pParent);
		virtual ~PlayerComponent() = default;

		virtual void Update() override;

		IdleState* GetIdleState() { return m_IdleState.get(); }
		HurtState* GetHurtState() { return m_HurtState.get(); }
		DeadState* GetDeadState() { return m_DeadState.get(); }

	private:
		PlayerState* m_pCurrentState;
		std::unique_ptr<IdleState> m_IdleState;
		std::unique_ptr<HurtState> m_HurtState;
		std::unique_ptr<DeadState> m_DeadState;
	};
}