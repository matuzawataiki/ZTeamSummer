#include "stdafx.h"
#include "EnemyStatus.h"

void EnemyStatusComponent::LoadFromJson(const std::string& filepath)
{
	/**
	  * NOTE::ここでJsonから読み込んだデータを呼び出す。
	  */
}

void EnemyStatusComponent::TakeDamage(int damageAmount)
{
	/** NOTE:: ここでアーマーやシールド、追加ライフがあると通常のHPより優先して減らすようにする。 */

	m_currentHP -= damageAmount;
	if (m_currentHP < 0) {
		m_currentHP = 0;
	}
}
