#include "stdafx.h"
#include "HelixRocket.h"
#include "Component/Skill/GunComponent.h"
#include "InGameObject/Ammo/HelixRocketAmmo.h"

void HelixRocket::Fire()
{
	auto gunComponent = GetComponent<GunComponent>();
	auto transformComponent = GetComponent<TransformComponent>();

	Vector3 eyeDirection = g_camera3D->GetForward();
	eyeDirection.Normalize();

	gunComponent->Fire(transformComponent->GetPosition(), eyeDirection);
}

void HelixRocket::Init()
{
	auto transform = GetComponent<TransformComponent>();
	transform->SetPosition(Vector3(0.0f, 170.0f, 0.0f));
}

bool HelixRocket::Start()
{
	m_gunData.fireRate = 0.1;
	m_gunData.maxAmmo = 10;

	m_ammoData.ammoName = "HelixRocket";
	m_ammoData.modelFilePath = "Assets/test/testAmmo.tkm";
	m_ammoData.thisCategory = EnCollisionCategory::enCollisionCat_PlayerBullet;
	m_ammoData.targetCategory = EnCollisionCategory::enCollisionCat_Enemy | EnCollisionCategory::enCollisionCat_Environment;
	m_ammoData.damage = 80;
	m_ammoData.speed = 500;
	m_ammoData.radius = 30;
	m_ammoData.range = 1000;
	m_ammoData.isProjectile = true;
	m_ammoData.ammoPoolSize = 5;
	m_ammoData.mass = 0;

	auto gunComponent = AddComponent<GunComponent>(m_gunData, m_ammoData);
	gunComponent->RegistAmmo<HelixRocketAmmo>();

	return true;
}
