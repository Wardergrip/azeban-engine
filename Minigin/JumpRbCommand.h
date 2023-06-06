#pragma once
#include "Command.h"
#include "RigidbodyComponent.h"
#include <glm/vec2.hpp>
#include "../3rdParty/box2d/box2d.h"
#include "PhysicsManager.h"
#include "Observer.h"

namespace aze
{
	class JumpRbCommand final : public Command, public Observer<PhysicsEvent>
	{
	public:
		JumpRbCommand(RigidbodyComponent* pRbComp, float force)
			:m_pRbComp{ pRbComp }
			, m_Force{ force }
			, m_JumpSent{false}
		{
			PhysicsManager::GetInstance().AddObserver(this);
		}
		virtual ~JumpRbCommand()
		{
			PhysicsManager::GetInstance().RemoveObserver(this);
		}

		void Execute() override
		{
			auto rbBody = m_pRbComp->GetBody();
			if ((std::abs(rbBody->GetLinearVelocity().y) > FLT_EPSILON) || m_JumpSent) return;
			rbBody->ApplyForce(b2Vec2{ 0, m_Force }, m_pRbComp->GetBody()->GetWorldCenter(), true);
			m_JumpSent = true;
		}

		void OnNotify(PhysicsEvent* /*data*/)
		{
			m_JumpSent = false;
		}

	private:
		RigidbodyComponent* m_pRbComp;
		float m_Force;
		bool m_JumpSent;
	};
}