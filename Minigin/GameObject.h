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
		void Update(float elapsedSec);
		void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		const Transform& GetTransform() const;
		Transform& GetTransform();

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template <typename T> std::weak_ptr<T> AddComponent();
		template <typename T> std::weak_ptr<T> GetComponent() const;
		template <typename T> bool HasComponent() const;
		template<typename T> bool RemoveComponent();

	private:
		std::vector<std::weak_ptr<Component>> m_pComponents;
		std::vector<std::shared_ptr<RenderComponent>> m_pRenderComponents;
		std::vector<std::shared_ptr<UpdateComponent>> m_pUpdateComponents;

		Transform m_transform{};
		// todo: mmm, every gameobject has a texture? Is that correct?
		std::shared_ptr<Texture2D> m_texture{};
	};

	template <typename T>
	inline std::weak_ptr<T> GameObject::AddComponent()
	{
#ifdef DEBUG
		bool isBased = std::is_base_of<Component, T>{}();
		assert(isBased && "Type is not a component.");
#endif // DEBUG


		auto pT = std::make_shared<T>();
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
		Component* pComponent = pT.get();
		pComponent->SetParent(weak_from_this());
		return weakComp;
	}

	template<typename T>
	inline std::weak_ptr<T> GameObject::GetComponent() const
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
	
	template<typename T>
	inline bool GameObject::HasComponent() const
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
	inline bool GameObject::RemoveComponent()
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

}
