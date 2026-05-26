#pragma once
#include "Component/State/IAIState.h"

class PunchAIState : public IAIState
{
public:
	PunchAIState() { 
		m_statePriority = 160;
		Active();
	}

public:
	void Enter() override { 
		m_stateTime = 1; 
		m_isIdle = false;
	}
	void Update() override;
	void Exit() override {}

};

