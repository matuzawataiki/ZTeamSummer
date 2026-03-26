#pragma once
#include "Component/State/IState.h"

class FlyState : public IState
{
	void Enter();
	void Update();
	void Exit();
};

