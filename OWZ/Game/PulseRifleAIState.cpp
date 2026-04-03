#include "stdafx.h"
#include "PulseRifleAIState.h"

PulseRifleAIState::PulseRifleAIState()
{
	m_statePriority = 110;
}

void PulseRifleAIState::Update()
{
	if (g_pad[0]->IsPress(enButtonLMouse)) {
		m_stateTime = 0.4f;
	}

	if (m_stateTime < 0) {
		m_stateTime = true;
	}
	else {
		m_stateTime -= g_gameTime->GetFrameDeltaTime();
	}
}

