#include "stdafx.h"
#include "BioticFieldState.h"
#include "InGameObject/Skill/SkillBase.h"
#include "Component/Graphics/ViewModelComponent.h"

void BioticFieldState::Enter()
{
	auto model = m_skill->GetParent()->GetComponent<ViewModelComponent>();
	model->PlayAnimation(2);

	m_skill->Fire();
}

void BioticFieldState::Update()
{
}

void BioticFieldState::Exit()
{
}
