#include "stdafx.h"
#include "GunComponent.h"
#include "Component/Skill/WeaponData.h"

GunComponent::GunComponent(GunData gunData, AmmoData ammoData)
{
	m_gunData = gunData;
	m_ammoData = ammoData;
}

void GunComponent::Fire(Vector3 position, Vector3 moveDirection)
{
	ProjectileManager::GetInstance()->UseAmmo(m_ammoData.ammoName, position, moveDirection);
}

void GunComponent::Reload()
{
	m_ammoCounter = m_gunData.maxAmmo;
}
