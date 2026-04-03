#pragma once
#include "Component/Skill/WeaponData.h"
class GunComponent : public Component
{
	appClass(GunComponent)
public:
	GunComponent(GunData gunData, AmmoData ammoData);
	~GunComponent() = default;
private:
	float m_fireRate;
	float m_range;
	float m_maxAmmo;
	float m_currentAmmo;
	
public:
	void Fire();
};

