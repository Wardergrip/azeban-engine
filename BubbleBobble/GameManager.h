#pragma once
#include <Singleton.h>
#include <Observer.h>
#include <Ev_Destroy.h>

namespace aze
{
	class GameObject;
	class GameManager final : public Singleton<GameManager>, Observer<Ev_Destroy<GameObject>>
	{
	public:
		void SetBobSpawnPoint(GameObject* ptr);
		GameObject* GetBobSpawnPoint() const;
		void SetBubSpawnPoint(GameObject* ptr);
		GameObject* GetBubSpawnPoint() const;

		void OnNotify(Ev_Destroy<GameObject>* data) override;
	protected:
		GameManager() = default;
		friend Singleton<GameManager>;

	private:
		GameObject* m_pBobSpawnPoint{ nullptr };
		GameObject* m_pBubSpawnPoint{ nullptr };
	};
}