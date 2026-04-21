#include "stdafx.h"
#include "ReloadAIState.h"

void ReloadAIState::Update()
{
	if (m_stateTime < 0) {
		m_isIdle = true;
	}
	else {
		m_stateTime -= g_gameTime->GetFrameDeltaTime();
	}
}