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

	void full_load();
}
