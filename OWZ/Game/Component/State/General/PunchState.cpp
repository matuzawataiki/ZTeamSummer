#include "stdafx.h"
#include "PunchState.h"
#include "InGameObject/Weapon/Punch.h"

void PunchState::Enter()
{
	m_wepon->Fire();
}

void PunchState::Update()
{
}

void PunchState::Exit()
{
}
