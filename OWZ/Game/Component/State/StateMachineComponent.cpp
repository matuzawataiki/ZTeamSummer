#include "stdafx.h"
#include "StateMachineComponent.h"
#include "IState.h"

StateMachineComponent::StateMachineComponent() = default;

StateMachineComponent::~StateMachineComponent() = default;

void StateMachineComponent::InitializeState(std::unique_ptr<IState> nextState)
{
	m_currentState = std::move(nextState);
	m_currentState->Enter();
}

void StateMachineComponent::Update()
{
	if (m_nextState) {
		m_currentState->Exit();
		m_currentState = std::move(m_nextState);
		m_currentState->Enter();
	}

	if(m_currentState){
		m_currentState->Update();
	}
}
