#include "stdafx.h"
#include "BioticFieldState.h"
#include "InGameObject/Skill/SkillBase.h"

void BioticFieldState::Enter()
{
	m_skill->Fire();
}

void BioticFieldState::Update()
{
}

void BioticFieldState::Exit()
{
}
