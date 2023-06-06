#include "PhysicsManager.h"
#include "../3rdParty/box2d/box2d.h"

#include <iostream>

//#define ENABLE_LEVEL_FLOOR

aze::PhysicsManager::~PhysicsManager()
{
}

void aze::PhysicsManager::EngineInit(int windowWidth, int windowHeight)
{
	m_b2World = std::make_unique<b2World>(b2Vec2{0,0});
	m_WindowWidth = windowWidth;
	m_WindowHeight = windowHeight;
#ifdef ENABLE_LEVEL_FLOOR
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
#endif // ENABLE_LEVEL_FLOOR
}

void aze::PhysicsManager::Init(float pixelsPerMeter, float gravityX, float gravityY)
{
	m_b2World->SetGravity(b2Vec2{ gravityX,gravityY });
	m_PixelsPerMeter = pixelsPerMeter;
	m_MetersPerPixel = (1.0f / pixelsPerMeter);
}

void aze::PhysicsManager::Step(float timeStep, int velocityIterations, int positionIterations)
{
	m_b2World->Step(timeStep, velocityIterations, positionIterations);
	PhysicsEvent data{};
	m_PhysicsEvent.NotifyObservers(&data);
}

glm::vec3 aze::PhysicsManager::b2toScreenSpace(const b2Vec2& pos)
{
	const float screenX = pos.x * m_PixelsPerMeter;
	const float screenY = m_WindowHeight - (pos.y * m_PixelsPerMeter);

	glm::vec3 screenPos{};
	screenPos.x = screenX;
	screenPos.y = screenY;
	return screenPos;
}

b2Vec2 aze::PhysicsManager::ScreenSpaceTob2(const glm::vec3& pos)
{
	b2Vec2 b2Pos{ pos.x * m_MetersPerPixel,(m_WindowHeight - pos.y) * m_MetersPerPixel };
	return b2Pos;
}

aze::PhysicsManager::PhysicsManager()
	:m_b2World{}
{
}
