#pragma once
#include "Component/State/IAIState.h"

class PulseRifleAIState : public IAIState
{
public:
	PulseRifleAIState();

public:
	void Enter() override { m_stateTime = 0.4; }
	void Update() override;
	void Exit() override {}


};

