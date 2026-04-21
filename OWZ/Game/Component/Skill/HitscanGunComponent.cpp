#include "stdafx.h"
#include "HitscanGunComponent.h"
#include "Component/Skill/WeaponData.h"

HitscanGunComponent::HitscanGunComponent(GunData gunData, AmmoData ammoData)
{
	m_gunData = gunData;
	m_ammoData = ammoData;
}

HitscanGunComponent::~HitscanGunComponent()
{
}

bool HitscanGunComponent::Fire(const Vector3& position, const Vector3& direction, HitResult& outResult)
{
	CollisionManager::GetInstance()->SphereCast(
		position,
		direction,
		m_ammoData.range,
		m_ammoData.radius,
		outResult,
		m_ammoData.targetCategory
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
