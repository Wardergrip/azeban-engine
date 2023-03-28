#pragma once
#include "Command.h"
#include "MovementComponent.h"
#include <memory>

namespace aze
{
	class MoveCommand : public Command
	{
	public:
		MoveCommand(std::weak_ptr<MovementComponent> pMovement, const glm::vec2& dir, float speed)
			:m_pMovement{pMovement}
			,m_Dir{dir}
			,m_Speed{speed}
		{}
		void Execute() override
		{
			m_pMovement.lock()->Move(glm::vec3{ m_Dir.r,m_Dir.g,0 }, m_Speed);
		}

	private:
		std::weak_ptr<MovementComponent> m_pMovement;
		glm::vec2 m_Dir;
		float m_Speed;
	};
}