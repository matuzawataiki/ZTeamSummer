#pragma once
#include "Component/State/IState.h"
#include "StateEnum.h"
class StateMachineComponent : public Component
{
	appClass(StateMachineComponent)
public:
	StateMachineComponent();
	~StateMachineComponent();
private:
	IState* m_currentMainState;
	IState* m_nextMainState;

	IState* m_currentMoveState;
	IState* m_nextMoveState;

	std::array<std::unique_ptr<IState>, EnMainStateID::enMainStateNum> m_mainStates;
	std::array<std::unique_ptr<IState>, EnMoveStateID::enMoveStateNum> m_moveStates;

public:
	void ChangeMainState(EnMainStateID nextState) {
		m_nextMainState = m_mainStates.at(nextState).get();
	}
	void ChangeMoveState(EnMoveStateID nextState) {
		m_nextMoveState = m_moveStates.at(nextState).get();
	}

	template <typename T>
	void RegisterMainState(EnMainStateID stateID) {
		auto state = std::make_unique<T>();
		m_mainStates.at(stateID) = std::move(state);
	}

	template <typename T>
	void RegisterMainState(EnMoveStateID stateID) {
		auto state = std::make_unique<T>();
		m_moveStates.at(stateID) = std::move(state);
	}

	void ResetState() {
		m_currentMainState = m_mainStates.at(EnMainStateID::enIdelState).get();
		m_currentMoveState = m_moveStates.at(EnMoveStateID::enMoveState).get();
	}

private:
	void Update() override;

};

