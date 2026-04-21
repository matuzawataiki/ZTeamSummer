#include "stdafx.h"
#include "HP.h"

float HP::AddDamege(float damege)
{
	if (m_maxHealth == 0) { return damege; }

	m_health -= damege;
	if (m_health < 0) {
		float damege = m_health;
		m_health = 0;
		return damege;
	}
	else {
		return 0;
	}
}

float HP::AddArmorDamege(float damege)
{
	if (m_maxHealth == 0) { return damege; }

	float armorDamege = damege * 0.8;
	m_health -= armorDamege;
	if (m_health < 0) {
		float damege = m_health;
		m_health = 0;
		return damege;
	}
	else {
		return 0;
	}
}

float HP::AddHeel(float heel)
{
	if (m_maxHealth == 0) { return heel; }

	m_health += heel;
	if (m_health > m_maxHealth) {
		float heel = m_maxHealth - m_health;
		m_health = m_maxHealth;
		return heel;
	}
	else {
		return 0;
	}
}

void Life::AddDamege(float damege)
{
	float damegeResult = damege;
	m_damageTimer = 5;

	for (int i = 0; i < enLifeTypeNum; i++) {
		damegeResult = m_lifes[i].AddDamege(damegeResult);
		if (damegeResult < 0.001) {
			break;
		}
	}
}

void Life::AddHeel(float heel)
{
	float heelResult = heel;

	for (int i = 0; i < enLifeTypeNum; i++) {
		heelResult = m_lifes[i].AddHeel(heelResult);
		if (heelResult < 0.001) {
			break;
		}
	}
}

void Life::Update()
{
	m_damageTimer -= g_gameTime->GetFrameDeltaTime();

	if (m_damageTimer < 0) {
		AddHeel(40 * g_gameTime->GetFrameDeltaTime());
	}

	if (m_damageTimer < 2) {
		m_lifes[EnLifeType::enShield].AddHeel(40 * g_gameTime->GetFrameDeltaTime());
	}

}
