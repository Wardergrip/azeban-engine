#include "LevelComponent.h"
#include "GameObject.h"

#include "RenderComponent.h"
#include "TextureObject.h"

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
		// LEVEL 
		if (pixel.col.r >= 250 && pixel.col.g >= 250 && pixel.col.b >= 250) // White
		{
			auto tile = CreateTile(tileSize, m_pGrid->GetPoint(pixel.point.x, pixel.point.y));

			m_pTiles.push_back(tile);
		}
		// PLATFORMS
		else if (pixel.col.r <= FLT_EPSILON && pixel.col.g >= 250 && pixel.col.b >= 250)
		{
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
	tile->SetPosition(pos.x, pos.y);

	tile->AddComponent<RenderComponent>();
	tile->AddComponent<TextureObject>("Small.png");

	return tile;
}
