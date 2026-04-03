#include "stdafx.h"
#include "StateControllerComponent.h"
#include "StateMachineComponent.h"

StateControllerComponent::~StateControllerComponent() {
	for (int i = 0; i < EnMainStateID::enMainStateNum; i++) {
		m_aiStates.at(i) = std::make_unique<IAIState>();
	}
}

bool StateControllerComponent::Start()
{
	return m_isInit;
}

void StateControllerComponent::Update()
{
	if (m_crrentStaet->IsIdle()) {
		m_nextStaet = m_aiStates.at(EnMainStateID::enIdelState).get();
	}

	ChangeCheck();

	if (m_nextStaet != m_crrentStaet) {
		m_crrentStaet->Exit();
		m_crrentStaet = m_nextStaet;
		m_nextStaet = nullptr;
		m_crrentStaet->Enter();
	}
}

void StateControllerComponent::ChangeCheck()
{
	if (ChangeRequest(enButtonLMouse, EnMainStateID::enMainWeaponState)) return;

	if (ChangeRequest(enButtonE, EnMainStateID::enFastSkillState)) return;

	if (ChangeRequest(enButtonQ, EnMainStateID::enSecondSkillState)) return;

	if (ChangeRequest(enButtonShift, EnMainStateID::enThirdSkillState)) return;

	if (ChangeRequest(enButtonR, EnMainStateID::enReloadState)) return;

	if (ChangeRequest(enButtonB, EnMainStateID::enAttackSkillState)) return;
}

bool StateControllerComponent::ChangeRequest(EnButton button, EnMainStateID stateID)
{
	if (!g_pad[0]->IsTrigger(button) ||	!m_aiStates.at(stateID)->IsActive()) {
		return false;
	}

	if (m_aiStates.at(stateID)->ChangeRequest(m_crrentStaet)) {
		m_nextStaet = m_aiStates.at(stateID).get();
		return true;
	}

	return false;
}
