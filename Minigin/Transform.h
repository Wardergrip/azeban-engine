#pragma once
#include <glm/glm.hpp>
#include <memory>
#include "Component.h"

namespace aze
{
	class Transform final : public Component<Transform>
	{
	public:
		Transform(GameObject* pParent, const glm::vec3& pos);
		Transform(GameObject* pParent, float x, float y, float z = 0.f);
		Transform(GameObject* pParent);

		void SetPosition(const glm::vec3& pos);
		void SetPosition(float x, float y, float z = 0.f);
		void SetWorldPosDirty();

		const glm::vec3& GetWorldPosition();
		const glm::vec3& GetLocalPosition() const;

	private:
		void UpdateWorldPos();

		bool m_IsWorldPosDirty;
		glm::vec3 m_WorldPosition;
		glm::vec3 m_LocalPosition;
	};
}
