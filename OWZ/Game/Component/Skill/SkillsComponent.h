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

private:
	std::unique_ptr<WeaponBase> m_mainWeapon;
	std::array<std::unique_ptr<SkillBase>, 4> m_skills;

public:
	void SetMainWepon(std::unique_ptr<WeaponBase> weapon) {
		m_mainWeapon = std::move(weapon);
	}
	WeaponBase* GetMainWepon() {
		return m_mainWeapon.get();
	}

	void SetSkill(std::unique_ptr<SkillBase> skill, EnSkillNumber skillNumber) {
		m_skills.at(skillNumber) = std::move(skill);
	}
	SkillBase* GetSkill(EnSkillNumber skillNumber) {
		return m_skills.at(skillNumber).get();
	}


private:
	void Update() override;
};

