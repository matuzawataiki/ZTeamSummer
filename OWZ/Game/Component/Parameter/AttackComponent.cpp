#include "stdafx.h"
#include "AttackComponent.h"

float AttackComponent::TryAttack()
{
	if (m_cooldown > 0.0f) { return 0.0f; }
	m_cooldown = 1.0f / m_param->m_fireRate;

	return m_param->m_damage;
}

void AttackComponent::Update()
{
	if (m_cooldown > 0.0f)
	{
		m_cooldown -= g_gameTime->GetFrameDeltaTime();
	}
}
