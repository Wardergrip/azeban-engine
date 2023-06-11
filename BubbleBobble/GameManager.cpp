#include "GameManager.h"
#include <GameObject.h>
#include <ServiceManager.h>

void aze::GameManager::SetBobSpawnPoint(GameObject* ptr)
{
	m_pBobSpawnPoint = ptr;
	m_pBobSpawnPoint->SubscribeOnDestroyEvent(this);
}

aze::GameObject* aze::GameManager::GetBobSpawnPoint() const
{
	return m_pBobSpawnPoint;
}

void aze::GameManager::SetBubSpawnPoint(GameObject* ptr)
{
	m_pBubSpawnPoint = ptr;
	m_pBubSpawnPoint->SubscribeOnDestroyEvent(this);
}

aze::GameObject* aze::GameManager::GetBubSpawnPoint() const
{
	return m_pBubSpawnPoint;
}

void aze::GameManager::SetPlayerMode(PlayerMode mode)
{
	m_Playermode = mode;
}

aze::PlayerMode aze::GameManager::GetPlayerMode() const
{
	return m_Playermode;
}

std::vector<aze::GameObject*>& aze::GameManager::GetEnemySpawnpoints()
{
	return m_pEnemySpawns;
}

void aze::GameManager::SetBobPlayer(GameObject* ptr)
{
	m_pPlayerBob = ptr;
	m_pPlayerBob->SubscribeOnDestroyEvent(this);
}

aze::GameObject* aze::GameManager::GetBobPlayer()
{
	return m_pPlayerBob;
}

void aze::GameManager::SetBubPlayer(GameObject* ptr)
{
	m_pPlayerBub = ptr;
	m_pPlayerBub->SubscribeOnDestroyEvent(this);
}

aze::GameObject* aze::GameManager::GetBubPlayer()
{
	return m_pPlayerBub;
}

void aze::GameManager::OnNotify(Ev_Destroy<GameObject>* data)
{
	auto destroyedObj = data->GetEntity();
	if (destroyedObj == m_pBobSpawnPoint)
	{
		m_pBobSpawnPoint = nullptr;
	}
	else if (destroyedObj == m_pBubSpawnPoint)
	{
		m_pBobSpawnPoint = nullptr;
	}
	else if (destroyedObj == m_pPlayerBob)
	{
		m_pPlayerBob = nullptr;
	}
	else if (destroyedObj == m_pPlayerBub)
	{
		m_pPlayerBub = nullptr;
	}
}

aze::GameManager::GameManager()
{
	ServiceManager::GetInstance().GetSoundSystem().Play("../Data/music.mp3",0.4f,-1);
}
