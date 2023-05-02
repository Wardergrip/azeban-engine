#pragma once
#include "SceneManager.h"
#include "GameObject.h"

namespace aze
{
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Adopt(std::unique_ptr<GameObject> object);
		void Adopt(GameObject* object);
		void Remove(GameObject* object);
		std::unique_ptr<GameObject> Abandon(GameObject* object);
		void RemoveAll();

		void Start();
		void Update();
		void Render() const;
		void OnGUI();

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
