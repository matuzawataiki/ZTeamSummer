#pragma once
#include "Component/State/IState.h"

class SkillBase;
class HelixRocketState : public IState
{
private:
	SkillBase* m_skill = nullptr;

public:
	void SetSkill(SkillBase* skill) { m_skill = skill; }

	void Enter() override;
	void Update() override;
	void Exit() override;

};

