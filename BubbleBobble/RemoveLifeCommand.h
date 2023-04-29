#pragma once
#include "Command.h"
#include "LivesComponent.h"
namespace aze
{
	class RemoveLifeCommand : public Command
	{
	public:
		RemoveLifeCommand(LivesComponent* livesC)
			:m_pLivesComponent{livesC}
		{}
		void Execute() override
		{
			m_pLivesComponent->RemoveLife();
		}

	private:
		LivesComponent* m_pLivesComponent;
	};
}