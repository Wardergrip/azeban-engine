#pragma once
#include <Command.h>
#include <SceneManager.h>
#include <Scene.h>

namespace aze
{
	class SkipLevelCommand final : public Command
	{
	public:
		SkipLevelCommand()
			:Command()
		{
		}

		void Execute() override
		{
			auto& sceneManager = SceneManager::GetInstance();
			const auto& activeSceneName = sceneManager.GetActiveScene()->GetName();
			if (activeSceneName == "Level1")
			{
				sceneManager.SetActiveScene("Level2");
			}
			else if (activeSceneName == "Level2")
			{
				sceneManager.SetActiveScene("Level3");
			}
			else if (activeSceneName == "Level3")
			{
				sceneManager.SetActiveScene("MainMenu");
			}
		}
	};
}