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
		if (pixel.col.r >= 250)
		{
			std::cout << "[" << p << "] " << pixel.point.x << " , " << pixel.point.y << "\n";
			auto tile = CreateTile();

			tile->GetTransform().SetPosition(m_pGrid->GetPoint(pixel.point.x, pixel.point.y));
			m_pTiles.push_back(tile);
		}
		else
		{
			auto tile = new GameObject(GetGameObject()->GetScene());
			GetGameObject()->Adopt(tile);

			tile->AddComponent<RenderComponent>();
			tile->AddComponent<TextureObject>("Yellow.png");

			tile->GetTransform().SetPosition(m_pGrid->GetPoint(pixel.point.x, pixel.point.y));
			m_pTiles.push_back(tile);

		}
		++p;
	}
	
	/*std::cout << "Done with making tiles\n";
	int i{ 0 };
	for (auto& tile : m_pTiles)
	{
		auto transform = tile->GetTransform();
		auto worldpos = transform.GetWorldPosition();
		std::cout << "[" << i << "] " << worldpos.x << " , " << worldpos.y << "\n";
		++i;
	}*/
}

aze::GameObject* aze::LevelComponent::CreateTile()
{
	auto tile = new GameObject(GetGameObject()->GetScene());
	GetGameObject()->Adopt(tile);

	tile->AddComponent<RenderComponent>();
	tile->AddComponent<TextureObject>("Small.png");

	return tile;
}
