#include "stdafx.h"
#include "SprintState.h"
#include "InGameObject/Skill/SkillBase.h"

void SprintState::Enter()
{
	m_skill->Fire();
}

void SprintState::Update()
{
}

void SprintState::Exit()
{
	m_skill->Reset();
}
