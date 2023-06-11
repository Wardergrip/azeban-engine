#pragma once
#include "Component.h"
#include "Grid.h"
#include "ImageParser.h"

#include <memory>

namespace aze
{
	class LevelComponent final : public Component
	{
	public:
		LevelComponent(GameObject* pParent, ImageParser* pImageParser);
		virtual ~LevelComponent();

	private:
		GameObject* CreateTile(float size, const glm::vec3& pos);

		std::unique_ptr<Grid> m_pGrid;
		std::vector<GameObject*> m_pTiles;
	};
}

