#pragma once
#include "InGameObject/Skill/SkillBase.h"

class HelixRocket : public SkillBase
{
public:
	HelixRocket() = default;
	~HelixRocket() = default;

private:
	GunData m_gunData;
	AmmoData m_ammoData;

public:
	void Fire()override;

public:
	bool Start() override;

};

