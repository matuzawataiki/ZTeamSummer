#pragma once
#include "Component/Skill/WeaponData.h"
#include "ProjectileManager.h"

class GunComponent : public Component
{
	appClass(GunComponent)
public:
	GunComponent(GunData gunData, AmmoData ammoData);
	~GunComponent() = default;
private:
	GunData m_gunData;
	AmmoData m_ammoData;

	int m_ammoCounter = 0;
	float m_fireRateCount = 0.0;

public:
	void Fire(Vector3 position, Vector3 moveDirection);

	bool CanFire() {
		if (m_fireRateCount >= 0) return false;
		if (m_ammoCounter <= 0) return false;

		return true;
	}

	void Reload();


	template<typename T>
	void RegistAmmo(){
		ProjectileManager::GetInstance()->RegistAmmo<T>(m_ammoData);
	}
};

