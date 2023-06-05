#pragma once
#include "Singleton.h"
#include "glm/glm.hpp"
#include <memory>

struct b2Vec2;
class b2World;
namespace aze
{ 
	class PhysicsManager final : public Singleton<PhysicsManager>
	{
	public:
		virtual ~PhysicsManager();

		void Init(float gravityX, float gravityY, int windowWidth, int windowHeight);

		void Step(float timeStep, int velocityIterations, int positionIterations);
		b2World* GetWorld() const { return m_b2World.get(); }

		glm::vec3 b2toScreenSpace(const b2Vec2& pos);
		b2Vec2 ScreenSpaceTob2(const glm::vec3& pos);
	protected:
		friend class Singleton<PhysicsManager>;
		PhysicsManager();

	private:
		std::unique_ptr<b2World> m_b2World;
		int m_WindowWidth;
		int m_WindowHeight;
	};
}

