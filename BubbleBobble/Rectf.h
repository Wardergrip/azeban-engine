#pragma once
#include <glm/vec3.hpp>

namespace aze
{
	struct Rectf final
	{
		glm::vec3 topLeft{};
		float width{};
		float height{};

		glm::vec3 Middle() const;

		bool IsOverlapping(const Rectf& other) const;
		bool IsOverlapping(const glm::vec3& point) const;
	};
}