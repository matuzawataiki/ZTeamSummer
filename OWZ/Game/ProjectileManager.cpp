#include "stdafx.h"
#include "ProjectileManager.h"
#include "InGameObject/Ammo/AmmoBase.h"

namespace {
	constexpr int FRAME_PER_CREATE = 3;
}

ProjectileManager* ProjectileManager::m_instance = nullptr;

ProjectileManager::ProjectileManager() = default;
ProjectileManager::~ProjectileManager() = default;

void ProjectileManager::UseAmmo(std::string name, Vector3 position, Vector3 moveDirection)
{
	AmmoPool& ammoPool = m_ammoPools.find(name)->second;
	int nextIndex = ammoPool.nextIndex;

	ammoPool.ammoPool.at(nextIndex)->GoAmmo(moveDirection, position);
	ammoPool.ammoPool.at(nextIndex)->Activate();

	ammoPool.nextIndex = ++nextIndex % ammoPool.ammoPool.size();

}


