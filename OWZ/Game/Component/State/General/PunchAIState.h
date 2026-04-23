#pragma once
#include "Component/State/IAIState.h"

class PunchAIState : public IAIState
{
public:
	PunchAIState() { m_statePriority = 160; }

public:
	void Enter() override { m_stateTime = 1; }
	void Update() override;
	void Exit() override {}

	bool ChangeRequest(IAIState* nextState) override;

};

