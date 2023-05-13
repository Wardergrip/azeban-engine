#pragma once
#include "Component.h"
#include "Grid.h"
#include "Rectf.h"
#include "ImageParser.h"

#include <memory>

namespace aze
{
	class LevelComponent final : public Component
	{
	public:
		LevelComponent(GameObject* pParent, ImageParser* pImageParser);

	private:
		GameObject* CreateTile(float size);

		std::unique_ptr<Grid> m_pGrid;
		std::vector<GameObject*> m_pTiles;
	};
}

