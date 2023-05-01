#include "Grid.h"

using namespace aze;

aze::Grid::Grid()
	:Grid(10,10,10.f,10.f)
{
}

aze::Grid::Grid(size_t horAmount, size_t vertAmount, float inbetweenWidth, float inbetweenHeight)
		:m_InbetweenWidth{inbetweenWidth}
		,m_InbetweenHeight{inbetweenHeight}
		, m_HorizontalPointsAmount{horAmount}
		, m_VerticalPointsAmount{vertAmount}
{
	CalculateGrid();
}

void Grid::SetTotalWidth(float width)
{
	m_InbetweenWidth = width / m_HorizontalPointsAmount;

	CalculateGrid();
}

void Grid::SetTotalHeight(float height)
{
	m_InbetweenHeight = height / m_VerticalPointsAmount;

	CalculateGrid();
}

void Grid::SetInbetweenWidth(float width)
{
	m_InbetweenWidth = width;

	CalculateGrid();
}

void Grid::SetInbetweenHeight(float height)
{
	m_InbetweenHeight = height;

	CalculateGrid();
}

void Grid::SetHorizontalPointsAmount(size_t amount)
{
	assert(amount > 1 && "Amount cannot be 0!");

	m_HorizontalPointsAmount = amount;
	CalculateGrid();
}

float aze::Grid::GetTotalWidth() const
{
	return m_HorizontalPointsAmount * m_InbetweenWidth;
}

float aze::Grid::GetTotalHeight() const
{
	return m_VerticalPointsAmount * m_InbetweenHeight;
}

float aze::Grid::GetInbetweenWidth() const
{
	return m_InbetweenWidth;
}

float aze::Grid::GetInbetweenHeight() const
{
	return m_InbetweenHeight;
}

size_t aze::Grid::GetVerticalPointsAmount() const
{
	return m_VerticalPointsAmount;
}

size_t aze::Grid::GetHorizontalPointsAmount() const
{
	return m_HorizontalPointsAmount;
}

std::vector<std::vector<glm::vec3>>& aze::Grid::GetGridMids()
{
	return m_GridMids;
}

const std::vector<std::vector<glm::vec3>>& aze::Grid::GetGridMids() const
{
	return m_GridMids;
}

const glm::vec3& aze::Grid::GetPoint(size_t x, size_t y)
{
	assert(y > 1 && y < m_GridMids.size() && "y out of range!");
	assert(x > 1 && x < m_GridMids.at(y).size() && "x out of range!");
	return m_GridMids.at(y).at(x);
}

void Grid::SetVerticalPointsAmount(size_t amount)
{
	assert(amount > 1 && "Amount cannot be 0!");

	m_VerticalPointsAmount = amount;
	CalculateGrid();
}

void Grid::CalculateGrid()
{
	for (auto& row : m_GridMids)
	{
		row.clear();
	}
	m_GridMids.clear();

	m_GridMids.reserve(m_VerticalPointsAmount);

	for (size_t i = 0; i < m_VerticalPointsAmount; i++)
	{
		m_GridMids.emplace_back(std::vector<glm::vec3>());
		m_GridMids.back().reserve(m_HorizontalPointsAmount);
		for (size_t j = 0; j < m_HorizontalPointsAmount; j++)
		{
			glm::vec3 point;
			point.x = j * m_InbetweenWidth;
			point.y = i * m_InbetweenHeight;
			point.z = 0.0f;
			m_GridMids.back().emplace_back(point);
		}
	}
}

std::vector<glm::vec3>::iterator Grid::begin()
{
	return m_GridMids.front().begin();
}

std::vector<glm::vec3>::iterator Grid::end()
{
	return m_GridMids.back().end();
}

std::vector<glm::vec3>::const_iterator Grid::begin() const
{
	return m_GridMids.front().cbegin();
}

std::vector<glm::vec3>::const_iterator Grid::end() const
{
	return m_GridMids.back().cend();
}
