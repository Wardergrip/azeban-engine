#pragma once
#include "SceneManager.h"
#include "Scene.h"

namespace aze
{
	void DemoScene(Scene& scene);
	void LevelOne(Scene& scene);
	void LevelTwo(Scene& scene);
	void LevelThree(Scene& scene);
	void Level(Scene& scene, const std::string& levelFilePath);
	void MainMenu(Scene& scene);
	void TestScene(Scene& scene);

	inline void full_load()
	{
		SceneManager::GetInstance().CreateScene("MainMenu",MainMenu);
		SceneManager::GetInstance().CreateScene("Level1", LevelOne);
		SceneManager::GetInstance().CreateScene("Level2", LevelTwo);
		SceneManager::GetInstance().CreateScene("Level3", LevelThree);
		//SceneManager::GetInstance().CreateScene("TestScene",TestScene);
	}
}
