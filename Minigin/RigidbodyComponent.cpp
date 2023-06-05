#include "RigidbodyComponent.h"
#include "../3rdParty/box2d/box2d.h"
#include "PhysicsManager.h"
#include "GameObject.h"

#include <iostream>

aze::RigidbodyComponent::RigidbodyComponent(GameObject* pParentGameObject, b2BodyDef* pBodyDef)
	:Component{ pParentGameObject }
{
	b2BodyDef bodyDef;
	if (pBodyDef)
	{
		bodyDef = *pBodyDef;
	}
	else
	{
		bodyDef.type = b2_dynamicBody;
	}
	m_b2Body = PhysicsManager::GetInstance().GetWorld()->CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;  
	fixtureDef.friction = 0.3f; 

	m_b2Body->CreateFixture(&fixtureDef); 
	GetGameObject()
		->GetTransform()
		.SetPosition(
			PhysicsManager::GetInstance().b2toScreenSpace(m_b2Body->GetPosition())
		);
}

aze::RigidbodyComponent::~RigidbodyComponent()
{
	PhysicsManager::GetInstance().GetWorld()->DestroyBody(m_b2Body);
}

void aze::RigidbodyComponent::Update()
{
	if (m_b2Body->GetType() == b2_staticBody) return;

	GetGameObject()
		->GetTransform()
		.SetPosition(
			PhysicsManager::GetInstance().b2toScreenSpace(m_b2Body->GetPosition())
		);
}
