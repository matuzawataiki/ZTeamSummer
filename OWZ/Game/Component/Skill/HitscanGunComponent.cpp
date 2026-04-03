#include "stdafx.h"
#include "HitscanGunComponent.h"
#include "Component/Skill/WeaponData.h"

HitscanGunComponent::HitscanGunComponent(GunData gunData, AmmoData ammoData)
{
	m_gunData = gunData;
	m_radius = ammoData.radius;
	m_range = ammoData.range;
	m_targetCategory = ammoData.targetCategory;
}

HitscanGunComponent::~HitscanGunComponent()
{
}

bool HitscanGunComponent::Fire(const Vector3& position, const Vector3& direction, HitResult& outResult)
{
	if (m_fireRateCount >= 0) return false;
	if (m_ammoCounter <= 0) return false;

	CollisionManager::GetInstance()->SphereCast(
		position,
		direction,
		m_range,
		m_radius,
		outResult,
		m_targetCategory
	);
	m_ammoCounter--;
	return true;
}

void HitscanGunComponent::Reload()
{
	m_ammoCounter = m_gunData.maxAmmo;
}

void HitscanGunComponent::Update()
{
	if (m_fireRateCount >= 0) {
		m_fireRateCount -= g_gameTime->GetFrameDeltaTime();
	}
}
