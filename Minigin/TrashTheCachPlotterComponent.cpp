#include "TrashTheCachPlotterComponent.h"
#include "../3rdParty/imgui/imgui.h"
#include "../3rdParty/imgui/imgui_plot.h"
#include "TrashTheCache.h"

void aze::TrashTheCachPlotterComponent::OnGUI()
{
    RenderExc1();
    RenderExc2();
}

void aze::TrashTheCachPlotterComponent::RenderExc1()
{
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 10, main_viewport->WorkPos.y + 50));
    ImGui::SetNextWindowSize(ImVec2(300, 400));

    if (!ImGui::Begin("Exercise 1"))
    {
        ImGui::End();
        return;
    }

    ImGui::InputInt("samples", &m_Exc1SampleAmount);

    if (ImGui::Button("Trash the cache"))
    {
        m_Exc1Samples.clear();
        auto avarages = TrashTheCache::GetAvaragesTest<size_t>(static_cast<size_t>(m_Exc1SampleAmount));
        m_Exc1Samples = TrashTheCache::ToFloatVector(avarages);
    }

    if (!m_Exc1Samples.empty())
    {
        RenderPlot(m_Exc1Samples, 4);
    }

    ImGui::End();
}

void aze::TrashTheCachPlotterComponent::RenderExc2()
{
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 310, main_viewport->WorkPos.y + 50));
    ImGui::SetNextWindowSize(ImVec2(300, 400));

    if (!ImGui::Begin("Exercise 2"))
    {
        ImGui::End();
        return;
    }

    ImGui::InputInt("samples", &m_Exc2SampleAmount);

    if (ImGui::Button("Trash the cache with GameObject3D"))
    {
        m_Exc2Samples.clear();
        auto avarages = TrashTheCache::GetAvaragesTest<TrashTheCache::GameObject3D>(static_cast<size_t>(m_Exc2SampleAmount));
        m_Exc2Samples = TrashTheCache::ToFloatVector(avarages);
    }

    if (!m_Exc2Samples.empty())
    {
        RenderPlot(m_Exc2Samples, 3);
    }

    if (ImGui::Button("Trash the cache with GameObject3DAlt"))
    {
        m_Exc2SamplesAlt.clear();
        auto avarages = TrashTheCache::GetAvaragesTest<TrashTheCache::GameObject3DAlt>(static_cast<size_t>(m_Exc2SampleAmount));
        m_Exc2SamplesAlt = TrashTheCache::ToFloatVector(avarages);
    }

    if (!m_Exc2SamplesAlt.empty())
    {
        RenderPlot(m_Exc2SamplesAlt, 3);
    }

    if (!m_Exc2Samples.empty() && !m_Exc2SamplesAlt.empty())
    {
        ImGui::Text("Combined:");

        {
            const float* doubleValues[2]{ m_Exc2Samples.data(), m_Exc2SamplesAlt.data() };
            ImU32 colors[2]{ ImColor{ 1.0f, 0.0f, 0.0f }, ImColor{ 0.0f, 1.0f, 0.0f } };

            ImGui::PlotConfig::Values plotValues{ nullptr, nullptr, static_cast<int>(m_Exc2Samples.size()), 0, 0, doubleValues, 2, colors };

            const float maxElement{ *std::max_element(m_Exc2Samples.begin(), m_Exc2Samples.end())};

            ImGui::PlotConfig plot{};
            plot.frame_size = ImVec2{ 200, 100 };
            plot.values = plotValues;
            plot.scale = ImGui::PlotConfig::Scale{ 0, maxElement };
            plot.grid_y = ImGui::PlotConfig::Grid{ true, maxElement / 10 };

            ImGui::Plot("doubleplotter", plot);
        }
    }

    ImGui::End();
}

void aze::TrashTheCachPlotterComponent::RenderPlot(const std::vector<float>& samples, size_t verticalLineIndex)
{
    ImGui::PlotConfig::Values plotValues{ nullptr, samples.data(), static_cast<int>(samples.size()), 0, ImColor{ 1.0f, 0.5f, 0.25f } };

    const float maxElement{ *std::max_element(begin(samples), end(samples)) };

    ImGui::PlotConfig plot{};
    plot.frame_size = ImVec2{ 200, 100 };
    plot.values = plotValues;
    plot.scale = ImGui::PlotConfig::Scale{ 0, maxElement };
    plot.v_lines = ImGui::PlotConfig::VerticalLines{ true, &verticalLineIndex, 1 };
    plot.grid_y = ImGui::PlotConfig::Grid{ true, maxElement / 10 };

    ImGui::Plot("plotter", plot);
}
