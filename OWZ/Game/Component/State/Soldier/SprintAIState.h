#pragma once
#include "Component/State/IAIState.h"

class SprintAIState : public IAIState
{
public:
	SprintAIState() { 
		m_statePriority = 130;
		Active();
	}

	void Enter() override;
	void Update() override;
	void Exit() override;

	bool ChangeRequest(IAIState* nextState) override;
	bool CanChange() override;
};

