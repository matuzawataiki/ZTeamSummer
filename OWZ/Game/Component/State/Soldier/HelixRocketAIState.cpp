#include "stdafx.h"
#include "HelixRocketAIState.h"
#include "InGameObject/Skill/SkillBase.h"

void HelixRocketAIState::Update()
{
	if (m_stateTime < 0) {
		m_isIdle = true;
	}
	else {
		m_stateTime -= g_gameTime->GetFrameDeltaTime();
	}
}

bool HelixRocketAIState::ChangeRequest(IAIState* nextState)
{
	if (m_statePriority <= nextState->GetPriority() && !m_lockFlag) {
		return true;
	}
	return false;
}

bool HelixRocketAIState::CanChange()
{
	return m_skill->CanFire();
}
