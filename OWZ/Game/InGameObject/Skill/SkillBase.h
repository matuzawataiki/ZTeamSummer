#pragma once
#include "Component/Skill/WeaponData.h"

class SkillBase : public GameObject
{
public:
	SkillBase();
	virtual ~SkillBase();

protected:
	bool m_isUse = false;
	bool m_canCooldown = true;
	float m_maxCooldown = 0;
	float m_cooldownTimer = 0;

public:
	virtual void Fire() = 0;
	virtual bool CanFire() {
		return !m_isUse && m_cooldownTimer <= 0 ? true : false;
	}
	virtual void Reset(){}

	bool IsUse() { return m_isUse; }

	void StartTimer() {
		m_canCooldown = true; 
		m_cooldownTimer = m_maxCooldown;
	}

	float GetCoolTime() { return m_cooldownTimer; }

protected:
	virtual bool Start() override { return true; }

	virtual void Update() override {
		if (m_cooldownTimer > 0 || m_canCooldown) {
			m_cooldownTimer -= g_gameTime->GetFrameDeltaTime();
		}
	}
};

