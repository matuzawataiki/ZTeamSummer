#include "stdafx.h"
#include "PunchAIState.h"

void PunchAIState::Update()
{
	if (m_stateTime < 0) {
		m_isIdle = true;
	}
	else {
		m_stateTime -= g_gameTime->GetFrameDeltaTime();
	}
}

bool PunchAIState::ChangeRequest(IAIState* nextState)
{
	if (m_statePriority < nextState->GetPriority() && !m_lockFlag) {
		return true;
	}
	return false;
}
