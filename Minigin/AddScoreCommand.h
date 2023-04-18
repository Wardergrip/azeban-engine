#pragma once
#include "Command.h"
#include "ScoreComponent.h"
namespace aze
{
	class AddScoreCommand : public Command
	{
	public:
		AddScoreCommand(ScoreComponent* livesC)
			:m_pScoreComponent{ livesC }
		{}
		void Execute() override
		{
			m_pScoreComponent->AddScore(10);
		}

	private:
		ScoreComponent* m_pScoreComponent;
	};
}