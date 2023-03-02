#pragma once
#include "Transform.h"
#include "Component.h"
#include "RenderComponent.h"
#include "UpdateComponent.h"
#include <memory>
#include <vector>
#include "Azemacros.h"

namespace aze
{
	class Texture2D;
	class Component;

	class GameObject final : public std::enable_shared_from_this<GameObject>
	{
	public:
		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update(float elapsedSec);
		void Render() const;

		void SetPosition(float x, float y);

		const Transform& GetTransform() const;
		Transform& GetTransform();

		template <typename T, typename... TArgs >
		std::weak_ptr<T> AddComponent(TArgs&&... targs)
		{
			[[maybe_unused]] const bool isBased = std::is_base_of<Component, T>{}();
			static_assert(isBased && "Type is not a component.");

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
			return weakComp;
		}

		template <typename T> 
		std::weak_ptr<T> GetComponent() const
		{
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
		bool m_IsMarkedForDestroy{ false };

		std::vector<std::weak_ptr<Component>> m_pComponents;
		std::vector<std::shared_ptr<RenderComponent>> m_pRenderComponents;
		std::vector<std::shared_ptr<UpdateComponent>> m_pUpdateComponents;

		Transform m_transform{};
	};
}
