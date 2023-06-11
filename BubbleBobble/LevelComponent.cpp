#include "LevelComponent.h"
#include "GameObject.h"

#include "RenderComponent.h"
#include "TextureObject.h"
#include "BoxColliderComponent.h"
#include "ColliderLayers.h"
#include "GameManager.h"

#include <iostream>


inline bool CheckForWhite(const SDL_Color& col)
{
	return (col.r >= 255) && (col.g >= 255) && (col.b >= 255);
}
inline bool CheckForCyan(const SDL_Color& col)
{
	return (col.r == 0) && (col.g >= 255) && (col.b >= 255);
}
inline bool CheckForBlue(const SDL_Color& col)
{
	return (col.r == 0) && (col.g == 0) && (col.b >= 255);
}
inline bool CheckForGreen(const SDL_Color& col)
{
	return (col.r == 0) && (col.g >= 255) && (col.b >= 255);
}


aze::LevelComponent::LevelComponent(GameObject* pParent, ImageParser* pImageParser)
	:Component(pParent)
{
	constexpr float tileSize{ 24 };
	GetGameObject()->SetPosition(0, 0);
	auto pixels = pImageParser->GetPixels();
	m_pGrid = std::make_unique<Grid>(pImageParser->GetWidth(), pImageParser->GetHeight(), tileSize, tileSize);
	for (auto& pixel : pixels)
	{
		// LEVEL 
		if (CheckForWhite(pixel.col))
		{
			auto tile = CreateTile(tileSize, m_pGrid->GetPoint(pixel.point.x, pixel.point.y));

			m_pTiles.push_back(tile);
		}
		// PLATFORMS
		else if (CheckForCyan(pixel.col))
		{
			auto tile = CreateTile(tileSize, m_pGrid->GetPoint(pixel.point.x, pixel.point.y));
			tile->GetComponent<BoxColliderComponent>()->SetLayer(layers::L_PLATFORM);
			m_pTiles.push_back(tile);
		}
		// BOB SPAWN (BLUE)
		else if (CheckForBlue(pixel.col))
		{
			auto spawnPoint = GetGameObject()->GetScene()->CreateGameObject();
			const auto& pos = m_pGrid->GetPoint(pixel.point.x, pixel.point.y);
			spawnPoint->SetPosition(pos.x, pos.y);
			GameManager::GetInstance().SetBobSpawnPoint(spawnPoint);
		}
		// BUB SPAWN (GREEN)
		else if (CheckForGreen(pixel.col))
		{
			auto spawnPoint = GetGameObject()->GetScene()->CreateGameObject();
			const auto& pos = m_pGrid->GetPoint(pixel.point.x, pixel.point.y);
			spawnPoint->SetPosition(pos.x, pos.y);
			GameManager::GetInstance().SetBubSpawnPoint(spawnPoint);
		}
	}
}

aze::GameObject* aze::LevelComponent::CreateTile(float size, const glm::vec3& pos)
{
	auto tile = new GameObject(GetGameObject()->GetScene());
	GetGameObject()->Adopt(tile);
	tile->SetPosition(pos.x, pos.y);

	tile->AddComponent<RenderComponent>();
	tile->AddComponent<TextureObject>("Small.png");
	tile->AddComponent<BoxColliderComponent>(size, size)->SetStatic(true);

	return tile;
}
