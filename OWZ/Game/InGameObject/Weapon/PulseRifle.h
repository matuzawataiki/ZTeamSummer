#pragma once
#include "InGameObject/Weapon/WeaponBase.h"

class PulseRifle : public WeaponBase
{
public:
	PulseRifle();
	~PulseRifle();
private:
	

public:
	void Fire()override;
	void Reload()override;

	bool IsFier();
private:
	bool Start() override;
	void Update() override;

};

