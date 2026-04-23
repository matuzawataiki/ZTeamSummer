#include "stdafx.h"
#include "ReloadState.h"
#include "InGameObject/Weapon/WeaponBase.h"

void ReloadState::Enter()
{
	m_weapon->Reload();
}

void ReloadState::Update()
{
}

void ReloadState::Exit()
{
}
