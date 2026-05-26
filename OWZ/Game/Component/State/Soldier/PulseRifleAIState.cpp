#include "stdafx.h"
#include "PulseRifleAIState.h"
#include "InGameObject/Weapon/WeaponBase.h"

void PulseRifleAIState::Update()
{
	if (m_stateTime <= 0) {
		m_isIdle = true;
	}
	else {
		if (m_wepon->GetAmmoCounter() <= 0) {
			m_stateTime = 0;
		}
		if (!g_pad[0]->IsPress(enButtonRB2)) {
			m_stateTime -= g_gameTime->GetFrameDeltaTime();
		}
	}
}

bool PulseRifleAIState::CanChange()
{
	if (m_wepon->GetAmmoCounter() > 0) return true;

	return false;
}