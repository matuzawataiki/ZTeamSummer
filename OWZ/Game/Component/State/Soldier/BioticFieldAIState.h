#pragma once
#include "Component/State/IAIState.h"

class SkillBase;
class BioticFieldAIState : public IAIState
{
public:
	BioticFieldAIState() { m_statePriority = 150; }

private:
	SkillBase* m_skill = nullptr;

	IAIState* m_exception = nullptr;

public:
	void SetSkill(SkillBase* skill) { m_skill = skill; }
	void SetException(IAIState* exception) { m_exception = exception; }

	void Enter() override { m_stateTime = 2; }
	void Update() override;
	void Exit() override {}

	bool ChangeRequest(IAIState* nextState) override;

};

