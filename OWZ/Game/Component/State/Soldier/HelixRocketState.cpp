#include "stdafx.h"
#include "HelixRocketState.h"
#include "InGameObject/Skill/SkillBase.h"

void HelixRocketState::Enter()
{
	m_skill->Fire();
}

void HelixRocketState::Update()
{
}

void HelixRocketState::Exit()
{
}
