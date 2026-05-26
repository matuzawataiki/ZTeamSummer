#include "stdafx.h"
#include "BioticFieldAIState.h"
#include "InGameObject/Skill/SkillBase.h"

void BioticFieldAIState::Update()
{
	if (m_stateTime < 0) {
		m_isIdle = true;
	}
	else {
		m_stateTime -= g_gameTime->GetFrameDeltaTime();
	}
}

bool BioticFieldAIState::ChangeRequest(IAIState* nextState)
{
	if (nextState == m_exception) {
		return false;
	}

	if (m_statePriority <= nextState->GetPriority() && !m_lockFlag) {
		return true;
	}
	return false;
}

bool BioticFieldAIState::CanChange()
{
	return m_skill->CanFire();
}
