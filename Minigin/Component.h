#pragma once
#include <memory>
namespace aze
{
	class GameObject;

	class Component
	{
	public:
		Component(std::weak_ptr<GameObject> pParent):m_pParentGameObject{pParent}{}
		Component(Component&& component) = default;
		Component(const Component& component) = default;
		Component& operator=(Component&& component) = default;
		Component& operator=(const Component& component) = default;
		virtual ~Component() = default;

		virtual void Render() const;
		virtual void Update(float elapsedSec);

		std::weak_ptr<GameObject> GetGameObject() const { return m_pParentGameObject; }
	private:
		std::weak_ptr<GameObject> m_pParentGameObject;
	};
}