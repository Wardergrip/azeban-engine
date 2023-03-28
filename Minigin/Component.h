#pragma once
#include <memory>
#include <stdexcept>
namespace aze
{
	class GameObject;

	class missing_component : public std::runtime_error
	{
	public:
		missing_component() :runtime_error(what()) {}
		const char* what() const override
		{
			return "A crucial component is not present";
		}
	};

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
		virtual void Update();
		virtual void OnGUI();

		std::weak_ptr<GameObject> GetGameObject() const { return m_pParentGameObject; }
	private:
		std::weak_ptr<GameObject> m_pParentGameObject;
	};
}