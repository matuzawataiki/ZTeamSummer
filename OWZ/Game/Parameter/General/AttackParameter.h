#pragma once
#include "Parameter/IMasterParameter.h"


struct AttackParameter : public IMasterParameter
{
	appParameter(AttackParameter)


	float m_damage = 0.0f;					// ダメージ
	float m_range = 0.0f;					// 攻撃範囲
	float m_fireRate = 0.0f;				// 攻撃の発射レート
};

