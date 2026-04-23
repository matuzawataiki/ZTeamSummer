#include "stdafx.h"
#include "Soldier.h"
#include "Component/Graphics/ViewModelComponent.h"
#include "Component/Collision/ColliderComponent.h"
#include "Component/Collision/RigidBodyComponent.h"
#include "Component/Status/StatusComponent.h"
#include "Component/Logic/CharacterMoveComponent.h"

//スキル
#include "Component/Skill/SkillsComponent.h"
#include "InGameObject/Weapon/PulseRifle.h"
#include "InGameObject/Skill/HelixRocket.h"
#include "InGameObject/Skill/BioticField.h"
#include "InGameObject/Skill/Sprint.h"

//ステート
#include "Component/State/StateMachineComponent.h"
#include "Component/State/StateControllerComponent.h"
#include "Component/State/Soldier/BioticFieldAIState.h"
#include "Component/State/Soldier/BioticFieldState.h"
#include "Component/State/Soldier/HelixRocketAIState.h"
#include "Component/State/Soldier/HelixRocketState.h"
#include "Component/State/Soldier/PulseRifleAIState.h"
#include "Component/State/Soldier/PulseRifleState.h"
#include "Component/State/Soldier/SprintAIState.h"
#include "Component/State/Soldier/SprintState.h"
#include "Component/State/General/IdleState.h"
#include "Component/State/General/PunchAIState.h"
#include "Component/State/General/PunchState.h"
#include "Component/State/General/ReloadAIState.h"
#include "Component/State/General/ReloadState.h"


Soldier::Soldier()
{
}

bool Soldier::Start()
{
	AddComponent<TransformComponent>();
	AddComponent<CharacterMoveComponent>();

	m_viewModelComponent = AddComponent<ViewModelComponent>();
	m_viewModelComponent->AddAnimation("Assets/Character/Playable/soldier76/animation/V_Idle.tka", true);
	m_viewModelComponent->AddAnimation("Assets/Character/Playable/soldier76/animation/V_AutoShot.tka", false);
	m_viewModelComponent->SetModel("Assets/Character/Playable/soldier76/model/soldierViewModel.tkm",true);
	m_viewModelComponent->SetDrawFlag(true);

	auto statusComponent = AddComponent<StatusComponent>();
	statusComponent->Init(Vector3(200, 50, 50), 6, 40);

	auto skillsComponent = AddComponent<SkillsComponent>();
	skillsComponent->SetMainWepon(std::move(std::make_unique<PulseRifle>()));
	skillsComponent->SetSkill(std::move(std::make_unique<HelixRocket>()), EnSkillNumber::enFastSkill);
	skillsComponent->SetSkill(std::move(std::make_unique<BioticField>()), EnSkillNumber::enSecondSkill);
	skillsComponent->SetSkill(std::move(std::make_unique<Sprint>()), EnSkillNumber::enThirdSkill);

	InitCollider();

	InitState();

	return true;
}

Soldier::~Soldier()
{
}

void Soldier::Update()
{
	Vector3 cameraPos = GetComponent<TransformComponent>()->GetPosition();
	cameraPos.y += 170.0f;

	g_camera3D->SetPosition(cameraPos);
}

void Soldier::Render()
{
	m_viewModelComponent->Draw();
}

void Soldier::InitCollider()
{
	auto colliderComponent = AddComponent<ColliderComponent>();
	auto rigidBodyComponent = AddComponent<RigidBodyComponent>();

	colliderComponent->CreateCapsule(50, 200);
	colliderComponent->SetCategory(EnCollisionCategory::enCollisionCat_Player);
	rigidBodyComponent->CreateRigidBody(10.0f);

}

void Soldier::InitState()
{
	auto stateMachineComponent = AddComponent<StateMachineComponent>();
	auto stateControllerComponent = AddComponent<StateControllerComponent>();
	auto skillComponent = GetComponent<SkillsComponent>();

	{
		auto state = std::make_unique<PulseRifleState>();
		state->SetWepon(skillComponent->GetMainWepon());
		stateMachineComponent->RegisterMainState(enMainWeaponState, std::move(state));
		stateControllerComponent->RegisterMainState<PulseRifleAIState>(enMainWeaponState);
	}

	{
		auto skill = skillComponent->GetSkill(EnSkillNumber::enFastSkill);
		auto state = std::make_unique<HelixRocketState>();
		state->SetSkill(skill);
		auto aiState = std::make_unique<HelixRocketAIState>();
		aiState->SetSkill(skill);

		stateMachineComponent->RegisterMainState(enSecondaryWeaponState,std::move(state));
		stateControllerComponent->RegisterMainState(enSecondaryWeaponState, std::move(aiState));
	}

	{
		auto skill = skillComponent->GetSkill(EnSkillNumber::enSecondSkill);
		auto state = std::make_unique<BioticFieldState>();
		state->SetSkill(skill);
		auto aiState = std::make_unique<BioticFieldAIState>();
		aiState->SetSkill(skill);

		stateMachineComponent->RegisterMainState(enFastSkillState, std::move(state));
		stateControllerComponent->RegisterMainState(enFastSkillState, std::move(aiState));
	}

	{
		auto skill = skillComponent->GetSkill(EnSkillNumber::enThirdSkill);
		auto state = std::make_unique<SprintState>();
		state->SetSkill(skill);

		stateMachineComponent->RegisterMainState(enSecondSkillState, std::move(state));
		stateControllerComponent->RegisterMainState<SprintAIState>(enSecondSkillState);
	}
}
