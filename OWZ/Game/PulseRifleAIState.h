#pragma once
#include "Component/State/IAIState.h"

class PulseRifleAIState : public IAIState
{
public:
	PulseRifleAIState();
	~PulseRifleAIState() = default;

private:

public:

	virtual void Enter() { m_stateTime = 0.4; }
	virtual void Update();
	virtual void Exit() {}


};

