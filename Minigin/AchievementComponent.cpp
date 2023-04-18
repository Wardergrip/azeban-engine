#include "AchievementComponent.h"
#include <isteamuserstats.h>

void aze::AchievementComponent::OnNotify(Ev_AddScore* event)
{
	if (event == nullptr) return;

	if (event->GetScore() == 500)
	{
		SteamUserStats()->SetAchievement("ACH_WIN_ONE_GAME");
	}
}
