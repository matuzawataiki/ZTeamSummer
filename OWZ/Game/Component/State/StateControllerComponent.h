#pragma once
#include "StateEnum.h"
#include "IAIState.h"

class StateMachineComponent;
class StateControllerComponent : public Component
{
	appClass(StateControllerComponent)
public:
	StateControllerComponent() = default;
	~StateControllerComponent();

private:
	bool m_isInit = false;
		
	IAIState* m_crrentStaet;
	IAIState* m_nextStaet;

	StateMachineComponent* m_stateMachine;
	std::array<std::unique_ptr<IAIState>, EnMainStateID::enMainStateNum> m_aiStates;

public:
	template <typename T>
	void RegisterMainState(EnMainStateID stateID) {
		auto state = std::make_unique<T>();
		m_aiStates.at(stateID) = std::move(state);
	}

	template <typename T>
	void RegisterMainState(EnMoveStateID stateID) {
		auto state = std::make_unique<T>();
		m_aiStates.at(stateID) = std::move(state);
	}

	void ResetState() {
		m_crrentStaet = m_aiStates.at(EnMainStateID::enIdelState).get();
		m_isInit = true;
	}

private:
	bool Start() override;
	void Update() override;

	void ChangeCheck();

	bool ChangeRequest(EnButton button, EnMainStateID stateID);

};
