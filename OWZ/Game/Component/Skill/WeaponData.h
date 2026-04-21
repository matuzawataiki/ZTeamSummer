#pragma once

struct GunData
{
	float fireRate = 0.0f;
	float maxAmmo = 0.0f;

};

struct AmmoData
{
	std::string modelFilePath;
	std::string ammoName;
	EnCollisionCategory thisCategory = EnCollisionCategory::enCollisionCat_None;
	uint32_t targetCategory = EnCollisionCategory::enCollisionCat_All;

	float damage = 0.0f;
	float speed = 0.0;
	float radius = 0.0f;
	float range = 0.0f;

	bool isProjectile = false;
	int ammoPoolSize = 1;
	float mass = 0.0f;
};