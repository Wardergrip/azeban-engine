#pragma once
#include "Transform.h"
#include "Component.h"
#include "RenderComponent.h"
#include "UpdateComponent.h"
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
			[[maybe_unused]] const bool isBased = std::is_base_of<Component, T>{}();
			static_assert(isBased && "Type is not a component.");
			[[maybe_unused]] const bool isTransform = std::is_same<Transform, T>{}();
			static_assert(!isTransform && "GameObject has transform by default. Cannot add more transforms than one.");

			auto pT = std::make_shared<T>(weak_from_this(), std::forward<TArgs>(targs)...);
			auto weakComp = std::weak_ptr<T>(pT);
			if constexpr (std::is_base_of<RenderComponent, T>{}())
			{
				m_pRenderComponents.push_back(pT);
			}
			else if constexpr (std::is_base_of<UpdateComponent, T>{}())
			{
				m_pUpdateComponents.push_back(pT);
			}
			m_pComponents.push_back(pT);
			pT->Start();
			return weakComp;
		}

		template <typename T> 
		std::weak_ptr<T> GetComponent() const
		{
			[[maybe_unused]] const bool isTransform = std::is_same<Transform, T>{}();
			static_assert(isTransform && "Illegal way to access transform. Use GameObject::GetTransform()");

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
			[[maybe_unused]] const bool isTransform = std::is_same<Transform, T>{}();
			static_assert(isTransform && "Cannot remove the transform from a GameObject");

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

		std::vector<std::weak_ptr<Component>> m_pComponents;
		std::vector<std::shared_ptr<RenderComponent>> m_pRenderComponents;
		std::vector<std::shared_ptr<UpdateComponent>> m_pUpdateComponents;

		std::unique_ptr<Transform> m_Transform;
	};
}
