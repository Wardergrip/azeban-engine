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
		if (pixel.col.r >= 250 && pixel.col.g >= 250 && pixel.col.b >= 250) // White
		{
			//std::cout << "[" << p << "] " << pixel.point.x << " , " << pixel.point.y << "\n";
			auto tile = CreateTile(tileSize);

			tile->GetTransform().SetPosition(m_pGrid->GetPoint(pixel.point.x, pixel.point.y));
			m_pTiles.push_back(tile);
		}
		++p;
	}
}

aze::GameObject* aze::LevelComponent::CreateTile(float /*size*/)
{
	auto tile = new GameObject(GetGameObject()->GetScene());
	GetGameObject()->Adopt(tile);

	tile->AddComponent<RenderComponent>();
	tile->AddComponent<TextureObject>("Small.png");

	return tile;
}
