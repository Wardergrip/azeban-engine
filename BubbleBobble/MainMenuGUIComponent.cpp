#include "MainMenuGUIComponent.h"
#include "../imgui/imgui.h"
#include "SceneManager.h"
#include "GameManager.h"
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
        // First tell the game manager what gamemode it is
        GameManager::GetInstance().SetPlayerMode(PlayerMode::singlePlayer);
        // Then load the scene with this information
        SceneManager::GetInstance().SetActiveScene("Level1");
        // After loading, this does not longer exist.
        ImGui::End();
        return;
    }
    if (ImGui::Button("Co-op"))
    {
        // First tell the game manager what gamemode it is
        GameManager::GetInstance().SetPlayerMode(PlayerMode::coop);
        // Then load the scene with this information
        SceneManager::GetInstance().SetActiveScene("Level1");
        // After loading, this does not longer exist.
        ImGui::End();
        return;
    }
    if (ImGui::Button("Versus"))
    {
        // First tell the game manager what gamemode it is
        GameManager::GetInstance().SetPlayerMode(PlayerMode::versus);
        // Then load the scene with this information
        SceneManager::GetInstance().SetActiveScene("Level1");
        // After loading, this does not longer exist.
        ImGui::End();
        return;
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
