#pragma once
#include "Command.h"
#include "MovementComponent.h"
#include "Observer.h"
#include "Ev_Destroy.h"
#include <memory>

namespace aze
{
	class MoveCommand : public Command, public Observer<Ev_Destroy<Component>>
	{
	public:
		MoveCommand(MovementComponent* pMovement, const glm::vec2& dir, float speed)
			:m_pMovement{pMovement}
			,m_Dir{dir}
			,m_Speed{speed}
		{
			pMovement->SubscribeOnDestroyEvent(this);
		}
		virtual ~MoveCommand()
		{
			if (m_pMovement) m_pMovement->UnsubscribeOnDestroyEvent(this);
		}
		void Execute() override
		{
			if (m_pMovement) m_pMovement->Move(glm::vec3{ m_Dir.r,m_Dir.g,0 }, m_Speed);
		}

		void OnNotify(Ev_Destroy<Component>* data) override
		{
			if (data->GetEntity() == m_pMovement)
			{
				m_pMovement = nullptr;
			}
		}

	private:
		MovementComponent* m_pMovement;
		glm::vec2 m_Dir;
		float m_Speed;
	};
}