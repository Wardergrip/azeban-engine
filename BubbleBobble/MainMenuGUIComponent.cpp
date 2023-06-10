#include "MainMenuGUIComponent.h"
#include "../imgui/imgui.h"
#include "SceneManager.h"
#include <sstream>

void aze::MainMenuGUIComponent::OnGUI()
{
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 60, main_viewport->WorkPos.y + 300));
    ImGui::SetNextWindowSize(ImVec2(130, 130));

    if (!ImGui::Begin("Main Menu"))
    {
        ImGui::End();
        return;
    }

    if (ImGui::Button("Single player"))
    {
        SceneManager::GetInstance().SetActiveScene("Level1");
    }
    if (ImGui::Button("Co-op"))
    {

    }
    if (ImGui::Button("Versus"))
    {

    }
    if (ImGui::Button("Score"))
    {
        m_ViewScores = !m_ViewScores;
    }

    ImGui::End();

    if (m_ViewScores)
    {
        ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 200, main_viewport->WorkPos.y + 300));
        if (!ImGui::Begin("Scores"))
        {
            ImGui::End();
            return;
        }

        auto& scoreEntries = m_ScoreSaver->GetScoreEntries();
        for (const auto& scoreEntry : scoreEntries)
        {
            std::stringstream ss;
            ss << scoreEntry.name[0] << scoreEntry.name[1] << scoreEntry.name[2] << ' ' << scoreEntry.score;
            ImGui::Text(ss.str().c_str());
        }

        ImGui::End();
    }
}
