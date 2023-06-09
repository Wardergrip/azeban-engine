#pragma once
#include "Component.h"

namespace aze
{
	class Transform;

	class RevolutionComponent final : public Component<RevolutionComponent>
	{
	public:
		RevolutionComponent(GameObject* pGameObjectParent, float radius = 10.f, float speed = 10.f);

		void Update() override;

		RevolutionComponent& SetRadius(float radius);
		RevolutionComponent& SetSpeed(float speed);

	private:
		float m_RotationAngle;
		float m_Radius;
		float m_Speed;
		Transform& m_ParentGameObjectTransform;
	};

}
