#pragma once
class IState;
class StateMachineComponent : public Component
{
	appClass(StateMachineComponent)
public:
	StateMachineComponent() = default;
	~StateMachineComponent() = default;
private:
	std::unique_ptr<IState> m_currentState;
	std::unique_ptr<IState> m_nextState;

public:
	void ChangeState(std::unique_ptr<IState>nextState) {
		m_nextState = std::move(nextState);
	}

	void InitializeState(std::unique_ptr<IState>nextState);
private:
	void Update() override;

};

