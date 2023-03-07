#pragma once
#include "Texture2D.h"
#include "Transform.h"
#include <string>

namespace aze
{
	class TextureObject : public Component
	{
	public:
		TextureObject(std::weak_ptr<GameObject> pParentGameObject, const std::string& fileName);
		TextureObject(TextureObject&& other) = delete;
		TextureObject(const TextureObject& other) = delete;
		TextureObject& operator=(TextureObject&& other) = delete;
		TextureObject& operator=(const TextureObject& other) = delete;
		~TextureObject() = default;

		TextureObject& SetTexture(const std::string& fileName);
		std::weak_ptr<Texture2D> GetTexture() const;

	private:
		std::shared_ptr<Texture2D> m_pTexture;
	};
}

