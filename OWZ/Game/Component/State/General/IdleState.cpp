#include "stdafx.h"
#include "IdleState.h"
#include "Component/Graphics/ViewModelComponent.h"

void IdleState::Enter()
{
	auto model = m_owner->GetComponent<ViewModelComponent>();
	model->PlayAnimation(0);

}

void IdleState::Update()
{
}

void IdleState::Exit()
{
}
