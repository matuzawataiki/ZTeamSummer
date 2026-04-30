#include "stdafx.h"
#include "PulseRifleState.h"
#include "InGameObject/Weapon/WeaponBase.h"
#include "Component/Graphics/ViewModelComponent.h"

void PulseRifleState::Enter()
{

}

void PulseRifleState::Update()
{
	if(g_pad[0]->IsPress(enButtonLMouse)){
		if (m_wepon->IsFier()) {
			auto model = m_wepon->GetParent()->GetComponent<ViewModelComponent>();
			model->PlayAnimation(1);

			m_wepon->Fire();
		}
	}
}

void PulseRifleState::Exit()
{

}
