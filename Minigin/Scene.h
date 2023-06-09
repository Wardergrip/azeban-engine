#pragma once
#include "SceneManager.h"
#include "GameObject.h"

namespace aze
{
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
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
		void Render() const;
		void OnGUI();

		const std::string& GetName() const { return m_name; }

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_name;
		std::vector < std::unique_ptr<GameObject>> m_objects{};

		static unsigned int m_idCounter; 
	};

}
