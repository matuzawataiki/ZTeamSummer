#pragma once
#include "Component/State/IState.h"

class IdleState : public IState
{
public:
	void Enter();
	void Update();
	void Exit();
};

