#pragma once
#include "Component/State/IAIState.h"
class SkillBase;
class HelixRocketAIState : public IAIState
{
public:
	HelixRocketAIState() {
		m_statePriority = 120;
		Active();
	}

private:
	SkillBase* m_skill = nullptr;

public:
	void SetSkill(SkillBase* skill) { m_skill = skill; }

	void Enter() override{ 
		m_stateTime = 2; 
		m_isIdle = false;
	}
	void Update() override;
	void Exit() override {}

	bool ChangeRequest(IAIState* nextState) override;
	bool CanChange() override;
};

