#pragma once
#include "Component.h"
#include <vector>
#include <chrono>

namespace aze
{
    class TrashTheCachPlotterComponent : public Component
    {
	public:
		TrashTheCachPlotterComponent(GameObject* pParent) :Component{ pParent } {}
		TrashTheCachPlotterComponent(TrashTheCachPlotterComponent&& component) = delete;
		TrashTheCachPlotterComponent(const TrashTheCachPlotterComponent& component) = delete;
		TrashTheCachPlotterComponent& operator=(TrashTheCachPlotterComponent&& component) = delete;
		TrashTheCachPlotterComponent& operator=(const TrashTheCachPlotterComponent& component) = delete;
		virtual ~TrashTheCachPlotterComponent() = default;

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

