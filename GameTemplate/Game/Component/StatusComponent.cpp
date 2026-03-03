#include "stdafx.h"
#include "StatusComponent.h"

void StatusComponent::Update()
{
}

void StatusComponent::Initialize(int maxhp, int attack)
{
	m_maxHP = maxhp;
	m_currentHP = maxhp;
	m_attack = attack;
}

void StatusComponent::ApplyDamage(int damage)
{
	if (damage <= 0)
	{
		return;
	}

	m_currentHP -= damage;

	if (m_currentHP <= 0)
	{
		m_currentHP = 0;
	}
}
