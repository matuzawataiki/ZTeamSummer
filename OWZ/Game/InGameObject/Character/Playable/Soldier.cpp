#include "stdafx.h"
#include "Soldier.h"
#include "Component/Graphics/ViewModelComponent.h"
#include "Component/Skill/SkillsComponent.h"
#include "Component/State/StateMachineComponent.h"
#include "Component/State/StateControllerComponent.h"
#include "InGameObject/Weapon/PulseRifle.h"

Soldier::Soldier()
{
}

bool Soldier::Start()
{
	AddComponent<TransformComponent>();
	AddComponent<ViewModelComponent>();
	AddComponent<SkillsComponent>();
	AddComponent<StateMachineComponent>();
	AddComponent<StateControllerComponent>();

	m_viewModelComponent = GetComponent<ViewModelComponent>();
	m_viewModelComponent->AddAnimation("Assets/Character/Playable/soldier76/animation/V_Idle.tka", true);
	m_viewModelComponent->AddAnimation("Assets/Character/Playable/soldier76/animation/V_AutoShot.tka", false);
	m_viewModelComponent->SetModel("Assets/Character/Playable/soldier76/model/soldierViewModel.tkm",true);
	m_viewModelComponent->SetDrawFlag(true);

	auto skillsComponent = GetComponent<SkillsComponent>();
	skillsComponent->SetMainWepon(std::make_unique<PulseRifle>());

	auto stateMachineComponent = GetComponent<StateMachineComponent>();



	return true;
}

Soldier::~Soldier()
{
}

void Soldier::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA)) {
		m_viewModelComponent->PlayAnimation(0);
	}
	if (g_pad[0]->IsPress(enButtonD)) {
		m_viewModelComponent->PlayAnimation(1);
	}
	if (m_viewModelComponent->IsPlay() == false) {
		m_viewModelComponent->PlayAnimation(0);

	}
}

void Soldier::Render()
{
	m_viewModelComponent->Draw();
}
