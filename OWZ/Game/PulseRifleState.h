#pragma once
#include "Component/State/IState.h"

class PulseRifle;
class PulseRifleState : public IState
{
public:
	PulseRifleState() = default;
	~PulseRifleState() = default;

private:
	PulseRifle* m_wepon = nullptr;

public:
	void SetWepon(PulseRifle* wepon) { m_wepon = wepon; }

	void Enter() override;
	void Update() override;
	void Exit() override;
};

