#pragma once
#include <glm/vec3.hpp>

namespace aze
{
	struct Rectf final
	{
		Rectf(glm::vec3 _topLeft = {}, float _width = 0, float _height = 0) 
			:topLeft{_topLeft}, width{_width}, height{_height} 
		{}

		glm::vec3 topLeft{};
		float width{};
		float height{};

		glm::vec3 Middle() const;

		bool IsOverlapping(const Rectf& other) const;
		bool IsOverlapping(const glm::vec3& point) const;
	};
}