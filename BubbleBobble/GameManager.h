#pragma once
#include <Singleton.h>
#include <vector>
#include <Observer.h>
#include <Ev_Destroy.h>

namespace aze
{
	enum class PlayerMode
	{
		singlePlayer, coop, versus
	};

	class GameObject;
	class GameManager final : public Singleton<GameManager>, Observer<Ev_Destroy<GameObject>>
	{
	public:
		void SetBobSpawnPoint(GameObject* ptr);
		GameObject* GetBobSpawnPoint() const;
		void SetBubSpawnPoint(GameObject* ptr);
		GameObject* GetBubSpawnPoint() const;
		void SetPlayerMode(PlayerMode mode);
		PlayerMode GetPlayerMode() const;
		std::vector<GameObject*>& GetEnemySpawnpoints();

		void SetBobPlayer(GameObject* ptr);
		GameObject* GetBobPlayer();
		void SetBubPlayer(GameObject* ptr);
		GameObject* GetBubPlayer();

		void OnNotify(Ev_Destroy<GameObject>* data) override;
	protected:
		GameManager() = default;
		friend Singleton<GameManager>;

	private:
		std::vector<GameObject*> m_pEnemySpawns;
		GameObject* m_pBobSpawnPoint{ nullptr };
		GameObject* m_pBubSpawnPoint{ nullptr };
		GameObject* m_pPlayerBob{ nullptr };
		GameObject* m_pPlayerBub{ nullptr };
		PlayerMode m_Playermode{ PlayerMode::singlePlayer };
	};
}