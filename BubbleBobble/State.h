#pragma once
namespace aze
{
	class State
	{
	public:
		State() = default;
		virtual ~State() = default;

		State(State&& other) = delete;
		State(const State& other) = delete;
		const State& operator=(State&& other) = delete;
		const State& operator=(const State & other) = delete;

		virtual void OnEnter() {}
		virtual State* OnHandle() { return this; }
		virtual void OnExit() {}
	};
}