#pragma once
#include "Component/State/IAIState.h"

class ReloadAIState : public IAIState
{
public:
	ReloadAIState() { m_statePriority = 140; }

	void Enter() override { m_stateTime = 3; }
	void Update() override;
	void Exit() override {}

};

