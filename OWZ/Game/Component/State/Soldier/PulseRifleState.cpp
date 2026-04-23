#include "stdafx.h"
#include "PulseRifleState.h"
#include "InGameObject/Weapon/WeaponBase.h"

void PulseRifleState::Enter()
{

}

void PulseRifleState::Update()
{
	if(g_pad[0]->IsPress(enButtonLMouse)){
		if (m_wepon->IsFier()) {
			m_wepon->Fire();
		}
	}
}

void PulseRifleState::Exit()
{

}
