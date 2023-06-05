#include "PhysicsManager.h"
#include "../3rdParty/box2d/box2d.h"

#include <iostream>

constexpr float PIXELS_PER_METER{ 16.f };
constexpr float METERS_PER_PIXEL{ 1.f / PIXELS_PER_METER };

aze::PhysicsManager::~PhysicsManager()
{
}

void aze::PhysicsManager::Init(float gravityX, float gravityY, int windowWidth, int windowHeight)
{
	m_b2World = std::make_unique<b2World>(b2Vec2{gravityX,gravityY});
	m_WindowWidth = windowWidth;
	m_WindowHeight = windowHeight;

	b2BodyDef bodyDef{};
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(0,-0.5f);
	auto body = m_b2World->CreateBody(&bodyDef);

	b2PolygonShape staticBox;
	staticBox.SetAsBox(1000.f, 1.0f); 

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &staticBox;
	fixtureDef.density = 1.0f; 
	fixtureDef.friction = 1.f;

	body->CreateFixture(&fixtureDef); 
}

void aze::PhysicsManager::Step(float timeStep, int velocityIterations, int positionIterations)
{
	m_b2World->Step(timeStep, velocityIterations, positionIterations);
}

glm::vec3 aze::PhysicsManager::b2toScreenSpace(const b2Vec2& pos)
{
	const float screenX = pos.x * PIXELS_PER_METER;
	const float screenY = m_WindowHeight - (pos.y * PIXELS_PER_METER);

	glm::vec3 screenPos{};
	screenPos.x = screenX;
	screenPos.y = screenY;
	return screenPos;
}

b2Vec2 aze::PhysicsManager::ScreenSpaceTob2(const glm::vec3& pos)
{
	b2Vec2 b2Pos{ pos.x * METERS_PER_PIXEL,(m_WindowHeight - pos.y) * METERS_PER_PIXEL };
	return b2Pos;
}

aze::PhysicsManager::PhysicsManager()
	:m_b2World{}
{
}
