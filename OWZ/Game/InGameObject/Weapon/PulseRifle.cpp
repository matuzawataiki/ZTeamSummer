#include "stdafx.h"
#include "PulseRifle.h"
#include "Component/Skill/HitscanGunComponent.h"
#include "Component/Math/TransformComponent.h"

PulseRifle::PulseRifle() = default;
PulseRifle::~PulseRifle() = default;

void PulseRifle::Fire()
{
	auto hitscanGunComponent = GetComponent<HitscanGunComponent>();
	auto transformComponent = GetComponent<TransformComponent>();

	Vector3 eyeDirection = g_camera3D->GetForward();
	eyeDirection.Normalize();

	HitResult hitResult;
	hitscanGunComponent->Fire(transformComponent->GetPosition(), eyeDirection, hitResult);
}

void PulseRifle::Reload()
{
	auto hitscanGunComponent = GetComponent<HitscanGunComponent>();
	hitscanGunComponent->Reload();
}

bool PulseRifle::IsFier()
{
	auto hitscanGunComponent = GetComponent<HitscanGunComponent>();
	return hitscanGunComponent->CanFire();
}

bool PulseRifle::Start()
{
	AddComponent<TransformComponent>();

	m_gunData.fireRate = 0.1;
	m_gunData.maxAmmo = 30;

	m_ammoData.radius = 1;
	m_ammoData.range = 1000;
	m_ammoData.targetCategory = EnCollisionCategory::enCollisionCat_Enemy | EnCollisionCategory::enCollisionCat_Environment;

	
	AddComponent<HitscanGunComponent>(m_gunData, m_ammoData);
	

	return true;
}

void PulseRifle::Update()
{
}
