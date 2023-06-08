#pragma once
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include "Singleton.h"

namespace aze
{
	class unregistered_scene : public std::runtime_error
	{
	public:
		unregistered_scene() :runtime_error(what()) {}
		const char* what() const override
		{
			return "Tried to set an active scene that is not registered with the scene manager. This means that the start function is not run on the scene.";
		}
	};

	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		virtual ~SceneManager();

		Scene& CreateScene(const std::string& name);

		void Start();
		void Update();
		void Render();
		void OnGUI();

		void SetActiveScene(Scene* pScene);
		void SetActiveScene(const std::string& sceneName);
		Scene* GetActiveScene();
	private:
		friend class Singleton<SceneManager>;
		SceneManager();
		std::vector<std::unique_ptr<Scene>> m_scenes;
		Scene* m_pActiveScene{ nullptr };
	};
}
