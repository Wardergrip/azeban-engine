#pragma once
#include "SceneManager.h"
#include "GameObject.h"
#include "CollisionManager.h"
#include <functional>

namespace aze
{
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name, const std::function<void(Scene&)>& loadFunc);
		friend void SceneManager::SetActiveScene(const std::string& sceneName);
	public:
		// Give ownership of a gameobject to the scene
		GameObject* Adopt(std::unique_ptr<GameObject> object);
		// Give ownership of a gameobject to the scene
		GameObject* Adopt(GameObject* object);
		// Remove a gameobject from the scene
		void Remove(GameObject* object);
		// Remove a gameobject from the scene and get ownership of it
		std::unique_ptr<GameObject> Abandon(GameObject* object);
		// Remove all gameobject from the scene
		void RemoveAll();

		// Creates a gameobject and automatically adds it to the scene
		GameObject* CreateGameObject() { return Adopt(new GameObject(this)); }

		void Start();
		void Update();
		void FixedUpdate();
		void Render() const;
		void OnGUI();
		void CleanUp();

		const std::string& GetName() const { return m_name; }
		CollisionManager& GetCollisionManager() { return m_CollisionManager; }

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		const std::function<void(Scene&)> GetLoadFunction() const { return m_LoadFunction; }

	private: 
		explicit Scene(const std::string& name, const std::function<void(Scene&)>& loadFunct);

		std::string m_name;
		std::vector < std::unique_ptr<GameObject>> m_objects{};
		CollisionManager m_CollisionManager;

		std::function<void(Scene&)> m_LoadFunction;

		static unsigned int m_idCounter; 
	};

}
