#include "stdafx.h"
#include "StateControllerComponent.h"
#include "StateMachineComponent.h"

StateControllerComponent::~StateControllerComponent() {
	for (int i = 0; i < EnMainStateID::enMainStateNum; i++) {
		m_aiStates.at(i) = std::make_unique<IAIState>();
	}
}

void StateControllerComponent::ResetState()
{
	m_crrentStaet = m_aiStates.at(EnMainStateID::enIdelState).get();
	m_isInit = true;
	m_stateMachine = m_owner->GetComponent<StateMachineComponent>();
}

bool StateControllerComponent::Start()
{
	return m_isInit;
}

void StateControllerComponent::Update()
{
	if (m_crrentStaet->IsIdle()) {
		m_nextStaet = EnMainStateID::enIdelState;
	}

	ChangeCheck();

	if (m_nextStaet != EnMainStateID::enMainStateNum) {
		auto nextState = m_aiStates.at(m_nextStaet).get();
		if (nextState != m_crrentStaet &&
			nextState != nullptr){
			m_crrentStaet->Exit();
			m_crrentStaet = nextState;
			m_crrentStaet->Enter();

			m_stateMachine->ChangeMainState(m_nextStaet);

			m_nextStaet = EnMainStateID::enMainStateNum;
		}
	}

	if (m_crrentStaet) {
		m_crrentStaet->Update();
	}
}

void StateControllerComponent::ChangeCheck()
{
	if (!g_pad[0]->IsPressAnyKey()) {
		return;
	}

	if (ChangeRequest(enButtonRB2, EnMainStateID::enMainWeaponState)) {
		return;
	}

	if (ChangeRequest(enButtonV, EnMainStateID::enSecondaryWeaponState)) {
		return;
	}

	if (ChangeRequest(enButtonRB1, EnMainStateID::enFastSkillState)) {
		return;
	}

	if (ChangeRequest(enButtonLB1, EnMainStateID::enSecondSkillState)) {
		return;
	}

	//if (ChangeRequest(enButtonSelect, EnMainStateID::enThirdSkillState)) {
	// return;
	//}

	if (ChangeRequest(enButtonY, EnMainStateID::enUltimateState)) {
		return;
	}

	if (ChangeRequest(enButtonX, EnMainStateID::enReloadState)) {
		return;
	}

	if (ChangeRequest(enButtonRB3, EnMainStateID::enAttackSkillState)) {
		return;
	}
}

bool StateControllerComponent::ChangeRequest(EnButton button, EnMainStateID stateID)
{
	if (!m_aiStates.at(stateID)) { return false; }

	if (!g_pad[0]->IsTrigger(button) ||	!m_aiStates.at(stateID)->IsActive()) {
		return false;
	}

	if (m_crrentStaet->ChangeRequest(m_aiStates.at(stateID).get())) {
		m_nextStaet = stateID;
		return true;
	}

	return false;
}
