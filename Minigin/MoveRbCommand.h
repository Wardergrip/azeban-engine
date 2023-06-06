#pragma once
#include "Command.h"
#include "RigidbodyComponent.h"
#include <glm/vec2.hpp>
#include "../3rdParty/box2d/box2d.h"

namespace aze
{
	class MoveRbCommand final : public Command
	{
	public:
		MoveRbCommand(RigidbodyComponent* pRbComp, const glm::vec2& dir, float speed)
			:m_pRbComp{ pRbComp }
			, m_Dir{ dir }
			, m_Speed{ speed }
		{}

		void Execute() override
		{
			m_pRbComp->GetBody()->ApplyForce(b2Vec2{ m_Dir.x * m_Speed, m_Dir.y * m_Speed }, m_pRbComp->GetBody()->GetWorldCenter(), true);
		}

	private:
		RigidbodyComponent* m_pRbComp;
		glm::vec2 m_Dir;
		float m_Speed;
	};
}