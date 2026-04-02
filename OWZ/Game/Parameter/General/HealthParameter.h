#pragma once
#include "Parameter/IMasterParameter.h"


struct HealthParameter : public IMasterParameter
{
	appParameter(HealthParameter)


	float m_maxHP = 100.0f;		// 最大体力
	float m_regenRate = 1.0f;	// 体力回復率
	bool m_canRevive = false;	// 復活可能かどうか
};

