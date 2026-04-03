#include "stdafx.h"
#include "StateMachineComponent.h"
#include "IState.h"

StateMachineComponent::StateMachineComponent() = default;

StateMachineComponent::~StateMachineComponent() = default;

void StateMachineComponent::Update()
{
	if (m_nextMoveState != m_currentMoveState) {
		m_currentMoveState->Exit();
		m_currentMoveState = m_nextMoveState;
		m_nextMoveState = nullptr;
		m_currentMoveState->Enter();
	}

	if (m_nextMainState != m_currentMainState) {
		m_currentMainState->Exit();
		m_currentMainState = m_nextMainState;
		m_nextMainState = nullptr;
		m_currentMainState->Enter();
	}

	if(m_currentMainState){
		m_currentMainState->Update();
	}
	if (m_currentMoveState){
		m_currentMoveState->Update();
	}
}
