#include "stdafx.h"
#include "HealthComponent.h"

void HealthComponent::TakeDamage(float amount)
{
	if (m_isDead) { return; }

	m_currentHP -= amount;

	if (m_currentHP <= 0.0f)
	{
		m_currentHP = 0.0f;
		m_isDead = true;
		if (onDead) { onDead(); }
	}
}

void HealthComponent::Heal(float amount)
{
	m_currentHP = (std::min)(m_currentHP + amount, m_param.m_maxHP);
}

void HealthComponent::Update()
{
	if (m_isDead) { return; }

	/** regenRateが設定されていたら自然回復 */
	if (m_param.m_regenRate > 0.0f)
	{
		Heal(m_param.m_regenRate * g_gameTime->GetFrameDeltaTime());
	}
}
