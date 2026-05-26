#include "stdafx.h"
#include "SprintAIState.h"
#include "Component/Collision/CharactorColliderComponent.h"

void SprintAIState::Enter()
{
	m_isIdle = false;
}

void SprintAIState::Update()
{
	float z = 0;

	z = g_pad[0]->GetLStickYF();

	if (z <= 0.5) {
		m_isIdle = true;
	}
}

void SprintAIState::Exit()
{
}

bool SprintAIState::ChangeRequest(IAIState* nextState)
{
	

	if (m_statePriority <= nextState->GetPriority() && !m_lockFlag){
		return true;
	}
	return false;
}

bool SprintAIState::CanChange()
{
	float z = 0;

	z = g_pad[0]->GetLStickYF();

	return z >= 0.5;
}
