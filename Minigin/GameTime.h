#pragma once
#include "Singleton.h"

namespace aze
{
	class GameTime final : public Singleton<GameTime>
	{
	public:
		GameTime() = default;

		float GetElapsed() const;
		void SetElapsed(float elapsed);
		float GetFixedTimeStep() const;
		void SetFixedTimeStep(float fixedTimeStep);

	private:
		float m_Elapsed;
		float m_FixedTimeStep;
	};
}

