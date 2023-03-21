#pragma once
#include "Component.h"
#include <vector>
#include <chrono>

namespace aze
{
    class PlotterComponent : public Component
    {
	public:
		PlotterComponent(std::weak_ptr<GameObject> pParent) :Component{ pParent } {}
		PlotterComponent(PlotterComponent&& component) = delete;
		PlotterComponent(const PlotterComponent& component) = delete;
		PlotterComponent& operator=(PlotterComponent&& component) = delete;
		PlotterComponent& operator=(const PlotterComponent& component) = delete;
		virtual ~PlotterComponent() = default;

		virtual void OnGUI() override;

	private:
		void RenderExc1();
		void RenderExc2();

		int m_Exc1SampleAmount{ 50 };
		int m_Exc2SampleAmount{ 50 };
		std::vector<float> m_Exc1Samples;
		std::vector<float> m_Exc2Samples;
		std::vector<float> m_Exc2SamplesAlt;

		void RenderPlot(const std::vector<float>& samples, size_t verticalLineIndex);
    };
}

