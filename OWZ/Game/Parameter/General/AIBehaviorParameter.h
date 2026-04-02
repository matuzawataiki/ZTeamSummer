#pragma once
#include "Parameter/IMasterParameter.h"


struct AIBehaviorParameter : public IMasterParameter
{
	appParameter(AIBehaviorParameter)


	float m_ditectionRange = 0.0f;		// 敵を発見する距離
};

