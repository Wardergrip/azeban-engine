#pragma once
#include <glm/vec3.hpp>
#include <iostream>

namespace aze
{
	struct Rect final
	{
		Rect(glm::vec3 _topLeft = {}, float _width = 0, float _height = 0)
			:topLeft{ _topLeft }, width{ _width }, height{ _height }
		{}
		Rect(float _width, float _height)
			:topLeft{ }, width{_width}, height{_height}
		{}

		glm::vec3 topLeft{};
		float width{};
		float height{};

		glm::vec3 GetMiddle() const
		{
			glm::vec3 middle;
			middle.x = topLeft.x + width / 2;
			middle.y = topLeft.y + height / 2;
			return middle;
		}

		Rect& SetMiddle(const glm::vec3& middle)
		{
			topLeft.x = middle.x - width / 2;
			topLeft.y = middle.y - height / 2;
			return *this;
		}

		bool IsOverlapping(const Rect& other) const
		{
			// If one rectangle is on left side of the other (if they don't overlap on x)
			if ((topLeft.x + width) < other.topLeft.x || (other.topLeft.x + other.width) < topLeft.x)
			{
				return false;
			}

			// If one rectangle is under the other (if they don't overlap on y)
			if (topLeft.y < (other.topLeft.y - other.height) || other.topLeft.y < (topLeft.y - height))
			{
				return false;
			}

			return true;
		}
		bool IsOverlapping(const glm::vec3& point) const
		{
			return (point.x >= topLeft.x && point.x <= topLeft.x + width) && (point.y >= topLeft.y && point.y <= topLeft.y + height);
		}
	};
}