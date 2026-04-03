#pragma once
#include "Component/Skill/WeaponData.h"
class AmmoBase : public GameObject
{
public:
	AmmoBase();
	virtual ~AmmoBase();

private:

public:
	virtual void Init(AmmoData ammoData) = 0;
	virtual void GoAmmo(Vector3 moveDirection, Vector3 position) = 0;

private:
	virtual bool Start() override { return true; }
	virtual void Update() override{}
};

