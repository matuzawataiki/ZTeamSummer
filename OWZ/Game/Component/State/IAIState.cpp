#include "stdafx.h"
#include "IAIState.h"

bool IAIState::ChangeRequest(IAIState* nextState)
{
	if (m_statePriority <= nextState->GetPriority() && !m_lockFlag) {
		return true;
	}
	return false;
}
