#pragma once
#include "Component.h"
namespace aze
{
	class TextObject;

	class FPS : public Component
	{
	public:
		FPS(std::weak_ptr<GameObject> pParentGameObject, std::weak_ptr<TextObject> pTextRenderer) 
			:Component{ pParentGameObject } 
			,m_pTextRenderer{pTextRenderer}
			,m_NrFramesPassed{ 0 }
			,m_TimeElapsed{ 0 }
			,m_UpdateInterval{ 1.f }
		{
		}
		FPS(FPS&& component) = default;
		FPS(const FPS& component) = default;
		FPS& operator=(FPS&& component) = default;
		FPS& operator=(const FPS& component) = default;
		virtual ~FPS() = default;

		void SetUpdateInterval(float interval);

		virtual void Update() override;
	private:
		std::weak_ptr<TextObject> m_pTextRenderer;
		int m_NrFramesPassed;
		float m_TimeElapsed;
		float m_UpdateInterval;
	};
}