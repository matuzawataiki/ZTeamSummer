#pragma once
#include "Component/State/IAIState.h"

class WeaponBase;
class PulseRifleAIState : public IAIState
{
public:
	PulseRifleAIState() {
		m_statePriority = 110;
		Active();
	}
private:
	WeaponBase* m_wepon = nullptr;

public:
	void SetWepon(WeaponBase* wepon) { m_wepon = wepon; }

	bool CanChange() override;

	void Enter() override {
		m_stateTime = 0.4;
		m_isIdle = false;
	}
	void Update() override;
	void Exit() override {}


};

