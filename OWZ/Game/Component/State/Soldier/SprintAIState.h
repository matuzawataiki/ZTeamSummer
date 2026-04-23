#pragma once
#include "Component/State/IAIState.h"

class SprintAIState : public IAIState
{
public:
	SprintAIState() { m_statePriority = 130; }

	void Enter() override;
	void Update() override;
	void Exit() override;

	virtual bool ChangeRequest(IAIState* nextState);
};

