#include "stdafx.h"
#include "HPData.h"
#include <algorithm>
#include <iostream>


/**
  * NOTE: {hoge,hoge}は左辺が現在のHP、右辺が最大HPを表す
  */
void HPData::Initialize(float base, float armor, float shield)
{
	m_baseHP = { base,base };
	m_armorHP = { armor,armor };
	m_shieldHP = { shield,shield };
	m_overHP = { 0.0f,1000.0f };
}


void HPData::ApplyDamage(float damageAmount)
{
	if (damageAmount > 0.0 && m_armorHP.m_currentHP > 0.0)
	{
		float reducedDamage = (std::max)(1.0f, damageAmount - 5.0f);
	}
	m_baseHP.m_currentHP -= damageAmount;
	if (m_baseHP.m_currentHP < 0)
	{
		m_baseHP.m_currentHP = 0;
		m_isDead = true;
	}
}


void HPData::ApplyHeal(float healAmount)
{
	m_baseHP.m_currentHP += healAmount;
	if (m_baseHP.m_currentHP > m_baseHP.m_maxHP)
	{
		m_baseHP.m_currentHP = m_baseHP.m_maxHP;
	}
}


float HPData::ProcessDamage(HPLayer&hplayer , float damageAmount)
{
	if (damageAmount <= 0.0)
	{
		return 0.0;
	}

	/**
	  * NOTE: シールドや追加ライフがある時はそちらからダメージを処理する
	  */
	if (hplayer.m_currentHP >= damageAmount)
	{
		hplayer.m_currentHP -= damageAmount;
		return 0.0;
	}


	/**
	  * NOTE: ダメージがシールドや追加ライフを超える場合は、超過した分をライフに適用する
	  */
	else
	{
		float overDamage = damageAmount - hplayer.m_currentHP;
		hplayer.m_currentHP = 0.0;
		return overDamage;
	}
}
