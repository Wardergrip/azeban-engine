#pragma once
#include <cstdint>

namespace aze
{
	namespace physicsFilters
	{
		constexpr uint16_t CATEGORY_LEVEL = 0x0001;
		constexpr uint16_t CATEGORY_PLAYER = 0x0002;
		constexpr uint16_t CATEGORY_PLATFORM = 0x0004;

		constexpr uint16_t MASK_PLAYER = CATEGORY_PLAYER | CATEGORY_PLATFORM;
		constexpr uint16_t MASK_PLATFORM = CATEGORY_PLAYER;
	}
}