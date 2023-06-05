#pragma once
#include "Component.h"

class b2Body;
struct b2BodyDef;
namespace aze
{
	class RigidbodyComponent final : public Component
	{
	public:
		RigidbodyComponent(GameObject* pParentGameObject, b2BodyDef* pBodyDef = nullptr);
		virtual ~RigidbodyComponent();

		RigidbodyComponent(RigidbodyComponent&& component) = delete;
		RigidbodyComponent(const RigidbodyComponent& component) = delete;
		RigidbodyComponent& operator=(RigidbodyComponent&& component) = delete;
		RigidbodyComponent& operator=(const RigidbodyComponent& component) = delete;

		void Update() override;

		b2Body* GetBody() const { return m_b2Body; }

	private:
		b2Body* m_b2Body;
	};
}
