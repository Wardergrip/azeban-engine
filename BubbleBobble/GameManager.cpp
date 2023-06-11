#include "GameManager.h"
#include <GameObject.h>

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

void aze::GameManager::OnNotify(Ev_Destroy<GameObject>* data)
{
	if (data->GetEntity() == m_pBobSpawnPoint)
	{
		m_pBobSpawnPoint = nullptr;
	}
	else if (data->GetEntity() == m_pBubSpawnPoint)
	{
		m_pBobSpawnPoint = nullptr;
	}
}
