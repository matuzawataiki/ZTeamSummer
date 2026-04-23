#pragma once
#include "Component/State/IState.h"

class WeaponBase;
class ReloadState : public IState
{
private:
	WeaponBase* m_weapon = nullptr;
public:
	void SetWeapon(WeaponBase* weapon) { m_weapon = weapon; }

	void Enter() override;
	void Update() override;
	void Exit() override;
};

