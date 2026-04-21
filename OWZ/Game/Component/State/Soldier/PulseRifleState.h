#pragma once
#include "Component/State/IState.h"

class WeaponBase;
class PulseRifleState : public IState
{
private:
	WeaponBase* m_wepon = nullptr;

public:
	void SetWepon(WeaponBase* wepon) { m_wepon = wepon; }

	void Enter() override;
	void Update() override;
	void Exit() override;
};

