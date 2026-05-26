#include "stdafx.h"
#include "ReloadState.h"
#include "InGameObject/Weapon/WeaponBase.h"
#include "Component/Graphics/ViewModelComponent.h"

void ReloadState::Enter()
{
	auto model = m_weapon->GetParent()->GetComponent<ViewModelComponent>();
	model->PlayAnimation(2);

	m_weapon->Reload();
}

void ReloadState::Update()
{
}

void ReloadState::Exit()
{
}
