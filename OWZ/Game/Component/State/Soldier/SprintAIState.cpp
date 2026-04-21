#include "stdafx.h"
#include "SprintAIState.h"

void SprintAIState::Enter()
{
}

void SprintAIState::Update()
{
	if (!g_pad[0]->IsPress(enButtonW) ||
		g_pad[0]->IsTrigger(enButtonShift) ||
		g_pad[0]->IsTrigger(enButtonRMouse) ||
		g_pad[0]->IsTrigger(enButtonLMouse)
		) {
		m_isIdle = true;
	}
}

void SprintAIState::Exit()
{
}

bool SprintAIState::ChangeRequest(IAIState* nextState)
{
	if (m_statePriority <= nextState->GetPriority() && !m_lockFlag && g_pad[0]->IsPress(enButtonW)){
		return true;
	}
	return false;
}
