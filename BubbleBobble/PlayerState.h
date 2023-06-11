#pragma once
namespace aze
{
	class PlayerComponent;
	class PlayerState
	{
	public:
		PlayerState(PlayerComponent* pPlayerComponent)
			:m_pPlayerComponent{pPlayerComponent}
		{
		}
		virtual ~PlayerState() = default;

		PlayerState(PlayerState&& other) = delete;
		PlayerState(const PlayerState& other) = delete;
		const PlayerState& operator=(PlayerState&& other) = delete;
		const PlayerState& operator=(const PlayerState & other) = delete;

		virtual void OnEnter() {}
		virtual PlayerState* OnHandle() { return this; }
		virtual void OnExit() {}
	protected:
		PlayerComponent* m_pPlayerComponent;
	};
}