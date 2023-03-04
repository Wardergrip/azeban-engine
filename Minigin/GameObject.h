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
		GameObject();
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update(float elapsedSec);
		void Render() const;

		void SetPosition(float x, float y);

		GameObject& SetParent(std::weak_ptr<GameObject> pParent, bool worldPositionStays = false);
		std::weak_ptr<GameObject> GetParent() const;
		size_t GetChildCount() const;
		std::weak_ptr<GameObject> GetChildAt(size_t index) const;
		const std::vector<std::weak_ptr<GameObject>>& GetChildren() const;

		const Transform& GetTransform() const;
		Transform& GetTransform();

		template <typename T, typename... TArgs >
		std::weak_ptr<T> AddComponent(TArgs&&... targs)
		{
			static_assert(std::is_base_of<Component, T>::value, "Type is not a component.");
			static_assert(!std::is_same<Transform, T>::value,"GameObject has transform by default. Cannot add more transforms than one.");
			static_assert(std::is_constructible<T, std::weak_ptr<GameObject>, TArgs...>::value, "TArgs do not result in a successful instantiation of T");

			auto pT = std::make_shared<T>(weak_from_this(), std::forward<TArgs>(targs)...);
			m_pComponents.push_back(pT);
			return pT;
		}

		template <typename T> 
		std::weak_ptr<T> GetComponent() const
		{
			static_assert(std::is_same<Transform, T>::value && "Illegal way to access transform. Use GameObject::GetTransform()");

			for (const auto& pComp : m_pComponents)
			{
				std::weak_ptr<T> derivedComp{ std::dynamic_pointer_cast<T>(pComp) };
				if (!aze::is_uninitialized(derivedComp))
				{
					return derivedComp;
				}
			}
			return nullptr;
		}

		template <typename T> 
		bool HasComponent() const
		{
			const bool isTransform = std::is_same<Transform, T>{}();
			if constexpr (isTransform) return true;

			for (const auto& pComp : m_pComponents)
			{
				std::weak_ptr<T> derivedComp{ std::dynamic_pointer_cast<T>(pComp) };
				if (!aze::is_uninitialized(derivedComp))
				{
					return true;
				}
			}
			return false;
		}

		template<typename T> 
		bool RemoveComponent()
		{
			static_assert(std::is_same<Transform, T>::value && "Cannot remove the transform from a GameObject");

			for (auto iterator{ m_pComponents.begin() }; iterator < m_pComponents.end(); ++iterator)
			{
				std::weak_ptr<T> derivedComp{ std::dynamic_pointer_cast<T>(*iterator) };
				if (aze::is_uninitialized(derivedComp))
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
		GameObject& AddChild(std::weak_ptr<GameObject> child);
		GameObject& RemoveChild(std::weak_ptr<GameObject> child);

		std::weak_ptr<GameObject> m_pParent;
		std::vector<std::weak_ptr<GameObject>> m_pChildren;
		bool m_IsMarkedForDestroy;

		std::vector<std::shared_ptr<Component>> m_pComponents;

		std::unique_ptr<Transform> m_Transform;
	};
}
