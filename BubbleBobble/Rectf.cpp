#include "Rectf.h"
#include <SDL.h>

glm::vec3 aze::Rectf::Middle() const
{
	glm::vec3 point;
	point.x = topLeft.x + width / 2;
	point.y = topLeft.y - height / 2;
	return point;
}

bool aze::Rectf::IsOverlapping(const glm::vec3& point) const
{
	return (point.x >= topLeft.x && point.x <= topLeft.x + width) && (point.y >= topLeft.y && point.y <= topLeft.y + height);
}

bool aze::Rectf::IsOverlapping(const Rectf& other) const
{
	// If one rectangle is on left side of the other (if they don't overlap on x)
	if ((topLeft.x + width) < other.topLeft.x || (other.topLeft.x + other.width) < topLeft.x)
	{
		return false;
	}

	// If one rectangle is under the other (if they don't overlap on y)
	if (topLeft.y < (other.topLeft.y + other.height) || other.topLeft.y < (topLeft.y + height))
	{
		return false;
	}

	return true;
}
