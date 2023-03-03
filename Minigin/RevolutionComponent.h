#pragma once
#include "UpdateComponent.h"

namespace aze
{
	class Transform;

	class RevolutionComponent final : public UpdateComponent
	{
	public:
		RevolutionComponent(std::weak_ptr<GameObject> pGameObjectParent, float radius = 10.f, float speed = 10.f);

		void Update(float elapsedSec) override;

		RevolutionComponent& SetRadius(float radius);
		RevolutionComponent& SetSpeed(float speed);

	private:
		float m_RotationAngle;
		float m_Radius;
		float m_Speed;
		Transform& m_ParentGameObjectTransform;
	};

}
