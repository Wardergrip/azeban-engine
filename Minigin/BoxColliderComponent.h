#pragma once
#include "Component.h"
#include "Rect.h"
#include "GameObject.h"
#include "CollisionManager.h"
#include "Ev_Collision.h"
#include "Subject.h"
#include "Renderer.h"
#include "Scene.h"

namespace aze
{
	class BoxColliderComponent final : public Component
	{
	public:
		BoxColliderComponent(GameObject* pParent, float width,float height)
			:Component{pParent}
			,m_Rect{ width,height }
			,m_IsStatic{false}
			,m_ColliderLayer{ globals::L_DEFAULT }
			,m_ColliderMask{ globals::M_DEFAULT }
		{
			GetGameObject()->GetScene()->GetCollisionManager().AddCollider(this);
			m_Rect.topLeft = GetGameObject()->GetTransform().GetWorldPosition();
		}
		virtual ~BoxColliderComponent()
		{
			GetGameObject()->GetScene()->GetCollisionManager().RemoveCollider(this);
		}

		/*virtual void Render() const override
		{
			auto sdlRenderer =  Renderer::GetInstance().GetSDLRenderer();
			SDL_Rect r;
			r.x = static_cast<int>(m_Rect.topLeft.x);
			r.y = static_cast<int>(m_Rect.topLeft.y);
			r.w = static_cast<int>(m_Rect.width);
			r.h = static_cast<int>(m_Rect.height);
			SDL_SetRenderDrawColor(sdlRenderer, 255, 0, 0, 255);
			if (SDL_RenderDrawRect(sdlRenderer, &r) != 0)
			{
				std::cout << SDL_GetError() << "\n";
			}
		}*/

		virtual void FixedUpdate() override
		{
			if (m_IsStatic) return;
			m_Rect.topLeft = GetGameObject()->GetTransform().GetWorldPosition();
		}

		const Rect& GetHitbox() const { return m_Rect; }
		void SetStatic(bool state) { m_IsStatic = state; }
		bool IsStatic() const { return m_IsStatic; }
		ColliderLayer GetLayer() const { return m_ColliderLayer; }
		ColliderMask GetMask() const { return m_ColliderMask; }
		void SetLayer(ColliderLayer layer) { m_ColliderLayer = layer; }
		void SetMask(ColliderMask mask) { m_ColliderMask = mask; }

		bool ShouldCollide(ColliderLayer otherLayer)
		{
			return (otherLayer & m_ColliderMask) != 0;
		}
		ColliderMask AddLayerToMask(ColliderLayer layer)
		{
			m_ColliderMask |= layer;
			return m_ColliderMask;
		}
		ColliderMask RemoveLayerFromMask(ColliderLayer layer)
		{
			m_ColliderMask &= ~layer;
			return m_ColliderMask;
		}

		void SubscribeOnCollision(Observer<Ev_Collision>* pObserver)
		{
			m_OnCollisionEvent.AddObserver(pObserver);
		}
		void UnsubscribeOnCollision(Observer<Ev_Collision>* pObserver)
		{
			m_OnCollisionEvent.RemoveObserver(pObserver);
		}

	private:
		friend void aze::CollisionManager::FixedUpdate();
		Rect m_Rect;
		bool m_IsStatic;
		ColliderLayer m_ColliderLayer;
		ColliderMask m_ColliderMask;
		Subject<Ev_Collision> m_OnCollisionEvent;
	};
}