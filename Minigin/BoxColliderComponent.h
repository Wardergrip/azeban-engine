#pragma once
#include "Component.h"
#include "Rect.h"
#include "GameObject.h"
#include "CollisionManager.h"
#include "Ev_Collision.h"
#include "Ev_TriggerOverlap.h"
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
			,m_IsTrigger{false}
			,m_ColliderLayer{ globals::L_DEFAULT }
			,m_ColliderMask{ globals::M_ALL }
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
		bool IsTrigger() const { return m_IsTrigger; }
		// Setting as trigger will change it's collidermask to M_DEFAULT.
		// If you don't want to set as trigger, you probably want to reset the collidermask to f.e. M_ALL
		void SetIsTrigger(bool state)
		{
			m_IsTrigger = state;
			if (m_IsTrigger)
			{
				SetMask(globals::M_DEFAULT);
			}
		}

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
		// Only works if this is a trigger
		void SubscribeOnTriggerOverlap(Observer<Ev_TriggerOverlap>* pObserver)
		{
			m_OnTriggerOverlapEvent.AddObserver(pObserver);
		}
		void UnsubscribeOnTriggerOverlap(Observer<Ev_TriggerOverlap>* pObserver)
		{
			m_OnTriggerOverlapEvent.RemoveObserver(pObserver);
		}

	private:
		friend void aze::CollisionManager::FixedUpdate();
		Rect m_Rect;
		bool m_IsStatic;
		bool m_IsTrigger;
		ColliderLayer m_ColliderLayer;
		ColliderMask m_ColliderMask;
		Subject<Ev_Collision> m_OnCollisionEvent;
		Subject<Ev_TriggerOverlap> m_OnTriggerOverlapEvent;
	};
}