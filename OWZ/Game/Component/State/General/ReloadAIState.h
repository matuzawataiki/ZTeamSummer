#pragma once
#include "Component/State/IAIState.h"

class ReloadAIState : public IAIState
{
public:
	ReloadAIState() {
		m_statePriority = 140;
		Active();
	}

	void Enter() override { 
		m_stateTime = 1;
		m_isIdle = false;
	}
	void Update() override;
	void Exit() override {}

};

