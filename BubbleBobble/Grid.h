#pragma once
#include <glm/glm.hpp>
#include <vector>

namespace aze
{
	class Grid
	{
	public:
		Grid();
		Grid(size_t horAmount, size_t vertAmount, float inbetweenWidth, float inbetweenHeight);
		~Grid() = default;
		Grid(const Grid& other) = delete;
		Grid(Grid&& other) = delete;
		Grid& operator=(const Grid& other) = delete;
		Grid& operator=(Grid&& other) = delete;

		void SetTotalWidth(float width);
		void SetTotalHeight(float height);
		void SetInbetweenWidth(float width);
		void SetInbetweenHeight(float height);
		void SetVerticalPointsAmount(size_t amount);
		void SetHorizontalPointsAmount(size_t amount);

		float GetTotalWidth() const;
		float GetTotalHeight() const;
		float GetInbetweenWidth() const;
		float GetInbetweenHeight() const;
		size_t GetVerticalPointsAmount() const;
		size_t GetHorizontalPointsAmount() const;

		std::vector<std::vector<glm::vec3>>& GetGridMids();
		const std::vector<std::vector<glm::vec3>>& GetGridMids() const;

		const glm::vec3& GetPoint(size_t x, size_t y);

		std::vector<glm::vec3>::iterator begin();
		std::vector<glm::vec3>::iterator end();
		std::vector<glm::vec3>::const_iterator begin() const;
		std::vector<glm::vec3>::const_iterator end() const;

	private:
		void CalculateGrid();

		float m_InbetweenWidth{};
		float m_InbetweenHeight{};
		size_t m_HorizontalPointsAmount{};
		size_t m_VerticalPointsAmount{};
		std::vector<std::vector<glm::vec3>> m_GridMids{};
	};
}