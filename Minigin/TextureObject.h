#pragma once
#include "RenderComponent.h"
#include "Texture2D.h"
#include "Transform.h"
#include <string>

namespace aze
{
	class TextureObject : public RenderComponent
	{
	public:
		TextureObject(std::weak_ptr<GameObject> pParentGameObject, const std::string& fileName);
		TextureObject(TextureObject&& other) = delete;
		TextureObject(const TextureObject& other) = delete;
		TextureObject& operator=(TextureObject&& other) = delete;
		TextureObject& operator=(const TextureObject& other) = delete;
		~TextureObject() = default;

		TextureObject* SetTexture(const std::string& fileName);
		std::weak_ptr<Texture2D> GetTexture() const;

		TextureObject& SetPosition(float x, float y);
		
		void Render() const override;
		void Update(float elapsedSec) override;

	private:
		std::shared_ptr<Texture2D> m_pTexture;
	};
}

