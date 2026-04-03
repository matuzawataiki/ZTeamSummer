#include "stdafx.h"
#include "ProjectileManager.h"
#include "InGameObject/Ammo/AmmoBase.h"

namespace {
	constexpr int FRAME_PER_CREATE = 3;
}

ProjectileManager::ProjectileManager() = default;
ProjectileManager::~ProjectileManager() = default;

void ProjectileManager::UseAmmo(std::string name, Vector3 moveDirection, Vector3 position)
{
	AmmoPool& ammoPool = m_ammoPools.find(name)->second;
	int nextIndex = ammoPool.nextIndex;

	ammoPool.ammoPool.at(nextIndex)->GoAmmo(moveDirection, position);
	ammoPool.ammoPool.at(nextIndex)->Activate();

	ammoPool.nextIndex = ++nextIndex % ammoPool.ammoPool.size();

}


