#pragma once
#include "InGameObject/Skill/SkillBase.h"

class Sprint : public SkillBase
{
public:
	void Fire() override;

	void Reset() override;
};

