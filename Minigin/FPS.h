#pragma once
#include "UpdateComponent.h"
namespace aze
{
	class TextObject;

	class FPS : public UpdateComponent
	{
	public:
		FPS() = default;
		FPS(std::weak_ptr<GameObject> pParent) :UpdateComponent{ pParent } {}
		FPS(FPS&& component) = default;
		FPS(const FPS& component) = default;
		FPS& operator=(FPS&& component) = default;
		FPS& operator=(const FPS& component) = default;
		virtual ~FPS() = default;

		void SetUpdateInterval(float interval);
		void SetTextureRenderer(std::weak_ptr<TextObject> pTextRenderer);

		virtual void Update(float elapsedSec) override;
	private:
		std::weak_ptr<TextObject> m_pTextRenderer;
		float m_TimeElapsed{ 0.f };
		float m_UpdateInterval{ 1.f };
	};
}