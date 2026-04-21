#pragma once
#include "InGameObject/Skill/SkillBase.h"

class HealingArea;
class BioticField : public SkillBase
{
public:
	BioticField();
	~BioticField();

public:
	std::unique_ptr<HealingArea> m_healingArea;
	float m_maxDuration = 0;
	float m_duration = 0;

public:
	void Init();

	void Fire() override;

	void Update() override;
};

