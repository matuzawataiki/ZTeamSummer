#include "stdafx.h"
#include "IAIState.h"

bool IAIState::ChangeRequest(IAIState* nextState)
{
	if (m_statePriority <= nextState->GetPriority() && !m_lockFlag && nextState->CanChange()) {
		return true;
	}
	return false;
}
