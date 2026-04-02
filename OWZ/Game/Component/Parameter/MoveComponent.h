#pragma once
#include "Parameter/General/MoveParameter.h"
#include "gameObject/Component.h"


class MoveComponent : public Component
{
	appClass(MoveComponent)


public:
	explicit MoveComponent(const MoveParameter& param): m_param(param) {}


	float GetMoveSpeed() const { return m_param.m_moveSpeed; }
	float GetJumpHeight() const { return m_param.m_jumpHeight; }


private:
	bool Start() override { return true; }


	void Update() override;


private:
	MoveParameter m_param;


};