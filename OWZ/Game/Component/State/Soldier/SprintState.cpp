#include "stdafx.h"
#include "SprintState.h"
#include "InGameObject/Skill/SkillBase.h"
#include "Component/Graphics/ViewModelComponent.h"

void SprintState::Enter()
{
	auto model = m_skill->GetParent()->GetComponent<ViewModelComponent>();
	model->PlayAnimation(4);

	m_skill->Fire();
}

void SprintState::Update()
{
}

void SprintState::Exit()
{
	m_skill->Reset();
}
