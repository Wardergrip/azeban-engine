#pragma once
#include "Singleton.h"
#include "glm/glm.hpp"
#include "Subject.h"
#include "PhysicsEvent.h"
#include <memory>

struct b2Vec2;
class b2World;
namespace aze
{ 
	class PhysicsManager final : public Singleton<PhysicsManager>
	{
	public:
		virtual ~PhysicsManager();

		void EngineInit(int windowWidth, int windowHeight);
		void Init(float pixelsPerMeter, float gravityX, float gravityY);

		void Step(float timeStep, int velocityIterations, int positionIterations);
		b2World* GetWorld() const { return m_b2World.get(); }

		glm::vec3 b2toScreenSpace(const b2Vec2& pos);
		b2Vec2 ScreenSpaceTob2(const glm::vec3& pos);

		void AddObserver(Observer<PhysicsEvent>* pObserver) { m_PhysicsEvent.AddObserver(pObserver); }
		void RemoveObserver(Observer<PhysicsEvent>* pObserver) { m_PhysicsEvent.RemoveObserver(pObserver); }

	protected:
		friend class Singleton<PhysicsManager>;
		PhysicsManager();

	private:
		float m_PixelsPerMeter;
		float m_MetersPerPixel;
		std::unique_ptr<b2World> m_b2World;
		int m_WindowWidth;
		int m_WindowHeight;
		Subject<PhysicsEvent> m_PhysicsEvent;
	};
}

