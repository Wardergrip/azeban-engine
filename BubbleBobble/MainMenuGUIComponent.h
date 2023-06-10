#pragma once
#include <Component.h>
#include "ScoreSaver.h"

namespace aze
{
	class MainMenuGUIComponent final : public Component
	{
	public:
		MainMenuGUIComponent(GameObject* pParent)
			:Component{pParent}
			,m_ViewScores{false}
		{
			m_ScoreSaver = std::make_unique<ScoreSaver>();
			m_ScoreSaver->ReadScoreEntries("../Data/scores.csv");
			m_ScoreSaver->SortScoreEntries();
		}
		virtual ~MainMenuGUIComponent() = default;

		virtual void OnGUI() override;

	private:
		bool m_ViewScores;
		std::unique_ptr<ScoreSaver> m_ScoreSaver;
		
	};
}
