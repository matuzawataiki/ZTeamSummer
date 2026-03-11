#include "stdafx.h"
#include "Soldier.h"
#include "Component/Graphics/ViewModelComponent.h"

Soldier::Soldier()
{
	AddComponent<TransformComponent>();
	AddComponent<ViewModelComponent>();

	m_model = GetComponent<ViewModelComponent>();
	//m_model->AddAnimation("Assets/Character/Playable/soldier76/animation/V_Idle.tka", true);
	m_model->SetModel("Assets/Character/Playable/soldier76/model/soldierViewModel.tkm");
	m_model->SetDrawFlag(true);
}

Soldier::~Soldier()
{
}

void Soldier::Render()
{
	m_model->Draw();
}
