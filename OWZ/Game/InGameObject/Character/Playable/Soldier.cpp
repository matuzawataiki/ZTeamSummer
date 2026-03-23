#include "stdafx.h"
#include "Soldier.h"
#include "Component/Graphics/ViewModelComponent.h"

Soldier::Soldier()
{
}

bool Soldier::Start()
{
	AddComponent<TransformComponent>();
	AddComponent<ViewModelComponent>();

	m_model = GetComponent<ViewModelComponent>();
	m_model->AddAnimation("Assets/Character/Playable/soldier76/animation/V_Idle.tka", true);
	m_model->AddAnimation("Assets/Character/Playable/soldier76/animation/V_AutoShot.tka", true);
	m_model->SetModel("Assets/Character/Playable/soldier76/model/soldierViewModel.tkm",true);
	m_model->SetDrawFlag(true);

	return true;
}

Soldier::~Soldier()
{
}

void Soldier::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA)) {
		m_model->PlayAnimation(0);
	}
	if (g_pad[0]->IsTrigger(enButtonD)) {
		m_model->PlayAnimation(1);
	}
}

void Soldier::Render()
{
	m_model->Draw();
}
