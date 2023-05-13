#pragma once
#include "Component.h"
#include "Rectf.h"

namespace aze
{ 
	class BoxColliderComponent : public Component
	{
	public:
		BoxColliderComponent(GameObject* pParent, const Rectf& hitbox);
		BoxColliderComponent(BoxColliderComponent&& component) = delete;
		BoxColliderComponent(const BoxColliderComponent& component) = delete;
		BoxColliderComponent& operator=(BoxColliderComponent&& component) = delete;
		BoxColliderComponent& operator=(const BoxColliderComponent& component) = delete;
		virtual ~BoxColliderComponent();

		const Rectf& GetRect() const;
		Rectf& GetRect();
		void SetRect(const Rectf& rect);

		Rectf GetHitbox() const;
		
		bool IsStatic() const { return m_IsStatic; }
		void SetStatic(bool value) { m_IsStatic = value; }

	private:
		Rectf m_Rect;
		bool m_IsStatic;
	};
}
