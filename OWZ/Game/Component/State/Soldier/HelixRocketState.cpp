#include "stdafx.h"
#include "HelixRocketState.h"
#include "InGameObject/Skill/SkillBase.h"
#include "Component/Graphics/ViewModelComponent.h"

void HelixRocketState::Enter()
{
	auto model = m_skill->GetParent()->GetComponent<ViewModelComponent>();
	model->PlayAnimation(5);
	m_skill->Fire();
}

void HelixRocketState::Update()
{
}

void HelixRocketState::Exit()
{
}
