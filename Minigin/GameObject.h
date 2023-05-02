#pragma once
#include "Transform.h"
#include "Component.h"
#include <memory>
#include <vector>
#include <stdexcept>
#include "Azemacros.h"

namespace aze
{
	class Texture2D;
	class Component;
	class Scene;

	class wrong_parent : public std::runtime_error
	{
	public:
		wrong_parent() :runtime_error(what()) {}
		const char* what() const override
		{
			return "Tried to remove a child from a parent that does not own the child";
		}
	};

	class child_is_nullptr : public std::runtime_error
	{
	public:
		child_is_nullptr() :runtime_error(what()) {}
		const char* what() const override
		{
			return "Child is nullptr";
		}
	};
	
	class GameObject final : public std::enable_shared_from_this<GameObject>
	{
	public:
		GameObject(Scene* pScene);
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Start();
		void Update();
		void Render() const;
		void OnGUI();

		void SetPosition(float x, float y);

		GameObject& SetParent(GameObject* pParent, bool worldPositionStays = false);
		GameObject& SetParent(std::nullptr_t null);
		GameObject& Adopt(std::unique_ptr<GameObject> pChild, bool worldPositionStays = false);
		GameObject& Adopt(GameObject* pChild, bool worldPositionStays = false);
		GameObject& RemoveChild(GameObject* pChild);
		std::unique_ptr<GameObject> Abandon(GameObject* pChild);
		GameObject* GetParent() const;
		size_t GetChildCount() const;
		GameObject* GetChildAt(size_t index) const;
		std::vector<GameObject*> GetChildren() const;

		Scene* GetScene() const;

		const Transform& GetTransform() const;
		Transform& GetTransform();

		template <typename T, typename... TArgs >
		T* AddComponent(TArgs&&... targs)
		{
			static_assert(std::is_base_of<Component, T>::value, "Type is not a component.");
			static_assert(!std::is_same<Transform, T>::value,"GameObject has transform by default. Cannot add more transforms than one.");
			static_assert(std::is_constructible<T, GameObject*, TArgs...>::value, "TArgs do not result in a successful instantiation of T");

			auto pT = std::make_unique<T>(this, std::forward<TArgs>(targs)...);
			auto p = pT.get();

			m_pComponents.push_back(std::move(pT));
			return p;
		}

		template <typename T> 
		T* GetComponent() const
		{
			static_assert(std::is_base_of<Component, T>::value, "Type is not a component.");
			static_assert(!std::is_same<Transform, T>::value, "Illegal way to access transform. Use GameObject::GetTransform()");

			for (const auto& pComp : m_pComponents)
			{
				T* compToFind{ dynamic_cast<T*>(pComp.get()) };
				if (compToFind) return compToFind;
			}
			return nullptr;
		}

		template <typename T> 
		bool HasComponent() const
		{
			static_assert(std::is_base_of<Component, T>::value, "Type is not a component.");

			const bool isTransform = std::is_same<Transform, T>{}();
			if constexpr (isTransform) return true;

			for (const auto& pComp : m_pComponents)
			{
				T* compToFind{ dynamic_cast<T*>(pComp.get()) };
				if (compToFind) return true;
			}
			return false;
		}

		template<typename T> 
		bool RemoveComponent()
		{
			static_assert(std::is_same<Transform, T>::value && "Cannot remove the transform from a GameObject");

			for (auto iterator{ m_pComponents.begin() }; iterator < m_pComponents.end(); ++iterator)
			{
				T* compToFind{ dynamic_cast<T*>((*iterator).get()) };
				if (compToFind)
				{
					m_pComponents.erase(iterator);
					return true;
				}
			}
			return false;
		}

		bool IsMarkedForDestroy() const;

		static void Destroy(GameObject* pGameObject);

	private:
		Scene* m_pScene;
		GameObject* m_pParent;
		std::vector<std::unique_ptr<GameObject>> m_pChildren;
		bool m_IsMarkedForDestroy;

		std::vector<std::unique_ptr<Component>> m_pComponents;

		std::unique_ptr<Transform> m_Transform;
	};
}
