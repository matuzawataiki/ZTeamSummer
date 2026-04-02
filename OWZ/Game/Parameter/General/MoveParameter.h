#pragma once
#include "Parameter/IMasterParameter.h"

struct MoveParameter : public IMasterParameter
{
	appParameter(MoveParameter)


	float m_moveSpeed = 0.0f;		// 移動速度
	float m_rotateSpeed = 0.0f;		// 回転速度
	float m_jumpHeight = 0.0f;		// ジャンプ力
};

