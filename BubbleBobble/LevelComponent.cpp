#include "LevelComponent.h"
#include "GameObject.h"

#include "RenderComponent.h"
#include "TextureObject.h"

#include "PhysicsManager.h"
#include "RigidbodyComponent.h"
#include "../3rdParty/box2d/box2d.h"

#include <iostream>

aze::LevelComponent::LevelComponent(GameObject* pParent, ImageParser* pImageParser)
	:Component(pParent)
{
	constexpr float tileSize{ 24 };
	GetGameObject()->SetPosition(0, 0);
	auto pixels = pImageParser->GetPixels();
	m_pGrid = std::make_unique<Grid>(pImageParser->GetWidth(), pImageParser->GetHeight(), tileSize, tileSize);
	int p{0};
	for (auto& pixel : pixels)
	{
		if (pixel.col.r >= 250 && pixel.col.g >= 250 && pixel.col.b >= 250) // White
		{
			//std::cout << "[" << p << "] " << pixel.point.x << " , " << pixel.point.y << "\n";
			auto tile = CreateTile(tileSize, m_pGrid->GetPoint(pixel.point.x, pixel.point.y));

			m_pTiles.push_back(tile);
		}
		++p;
	}
}

aze::GameObject* aze::LevelComponent::CreateTile(float /*size*/, const glm::vec3& pos)
{
	auto tile = new GameObject(GetGameObject()->GetScene());
	GetGameObject()->Adopt(tile);
	//tile->SetPosition(pos.x, pos.y);

	tile->AddComponent<RenderComponent>();
	tile->AddComponent<TextureObject>("Small.png");

	b2BodyDef bodyDef{};
	bodyDef.type = b2_staticBody;
	auto b2Pos = PhysicsManager::GetInstance().ScreenSpaceTob2(pos);
	bodyDef.position.Set(b2Pos.x,b2Pos.y);
	auto body = tile->AddComponent<RigidbodyComponent>(&bodyDef)->GetBody();

	b2PolygonShape staticBox;
	staticBox.SetAsBox(1.0f, 1.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &staticBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 1.f;

	body->CreateFixture(&fixtureDef);

	return tile;
}
