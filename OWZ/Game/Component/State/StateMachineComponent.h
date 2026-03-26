#pragma once
#include "Component/State/IState.h"

class StateMachineComponent : public Component
{
	appClass(StateMachineComponent)
public:
	StateMachineComponent();
	~StateMachineComponent();
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

