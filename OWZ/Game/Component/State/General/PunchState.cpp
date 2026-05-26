#include "stdafx.h"
#include "PunchState.h"
#include "InGameObject/Weapon/Punch.h"
#include "Component/Graphics/ViewModelComponent.h"


void PunchState::Enter()
{
	auto model = m_weapon->GetParent()->GetComponent<ViewModelComponent>();
	model->PlayAnimation(2);

	m_weapon->Fire();
}

void PunchState::Update()
{
}

void PunchState::Exit()
{
}
