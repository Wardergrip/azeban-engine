#pragma once
namespace aze
{
	void DemoScene();
	void LevelOne();
	void MainMenu();

	inline void full_load()
	{
		MainMenu();
		//DemoScene();
		LevelOne();
	}
}
