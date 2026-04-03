#pragma once

#include "InGameObject/Weapon/WeaponBase.h"
#include "InGameObject/Skill/SkillBase.h"

enum EnSkillNumber
{
	enFastSkill,
	enSecondSkill,
	enThirdSkill,
	enSubSkill
};

class SkillsComponent : public Component
{
	appClass(SkillsComponent)
public:
	SkillsComponent();
	~SkillsComponent();

	void SetMainWepon(std::unique_ptr<WeaponBase> weapon) {
		m_mainWeapon = std::move(weapon);
	}

private:
	std::unique_ptr<WeaponBase> m_mainWeapon;
	std::array<SkillBase, 4> m_skills;
};

