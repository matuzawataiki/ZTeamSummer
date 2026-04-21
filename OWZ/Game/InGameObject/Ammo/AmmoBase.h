#pragma once
#include "Component/Skill/WeaponData.h"
class AmmoBase : public GameObject
{
public:
	AmmoBase();
	virtual ~AmmoBase();

public:
	virtual void Init(AmmoData ammoData) = 0;
	virtual void GoAmmo(Vector3 moveDirection, Vector3 position) = 0;

	virtual bool Start() override { return true; }
	virtual void Update() override{}
};

