#pragma once
#include "Component/Skill/WeaponData.h"


class WeaponBase : public GameObject
{
public:
	WeaponBase();
	virtual ~WeaponBase();

protected:
	GunData m_gunData;
	AmmoData m_ammoData;

public:
	virtual void Fire(){}
	virtual void Reload(){}

private:
	virtual bool Start() override { return true; }
	virtual void Update() override{}
};

