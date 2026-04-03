#pragma once
#include "Component/Skill/WeaponData.h"
class HitscanGunComponent : public Component
{
	appClass(HitscanGunComponent)
public:
	HitscanGunComponent(GunData gunData, AmmoData ammoData);
	~HitscanGunComponent();

private:
	GunData m_gunData;
	uint32_t m_targetCategory = EnCollisionCategory::enCollisionCat_All;
	int m_ammoCounter = 0;
	float m_radius = 0.0f;
	float m_range = 0.0f;

	float m_fireRateCount = 0.0;
public:
	bool Fire(const Vector3& position, const Vector3& direction, HitResult& outResult);

	bool CanFire() {
		if (m_fireRateCount >= 0) return false;
		if (m_ammoCounter <= 0) return false;

		return true;
	}

	void Reload();

private:
	void Update()override;


};

