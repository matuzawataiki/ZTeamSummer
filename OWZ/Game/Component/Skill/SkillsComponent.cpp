#include "stdafx.h"
#include "SkillsComponent.h"
#include "InGameObject/Weapon/WeaponBase.h"
#include "InGameObject/Skill/SkillBase.h"

void SkillsComponent::Update()
{
	if(m_mainWeapon){
		m_mainWeapon->StartWrapper();
		m_mainWeapon->UpdateWrapper();
	}

	for (int i = 0; i < m_skills.size(); i++) {
		if (m_skills.at(i)) {
			m_skills.at(i)->StartWrapper();
			m_skills.at(i)->UpdateWrapper();
		}
	}
}
