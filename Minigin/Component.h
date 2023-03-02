#pragma once
#include <memory>
namespace aze
{
	class GameObject;

	class Component
	{
	public:
		Component(std::weak_ptr<GameObject> pParent):m_pParent{pParent}{}
		Component(Component&& component) = default;
		Component(const Component& component) = default;
		Component& operator=(Component&& component) = default;
		Component& operator=(const Component& component) = default;
		virtual ~Component() = default;
	
		std::weak_ptr<GameObject> GetParent() const { return m_pParent; }
	private:
		std::weak_ptr<GameObject> m_pParent;
	};
}