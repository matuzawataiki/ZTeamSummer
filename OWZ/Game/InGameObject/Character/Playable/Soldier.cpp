#include "stdafx.h"
#include "Soldier.h"
#include "Component/Graphics/ViewModelComponent.h"
#include "Component/Collision/ColliderComponent.h"
#include "Component/Collision/RigidBodyComponent.h"
#include "Component/Collision/CharactorColliderComponent.h"
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
#include "Component/State/General/IdleAIState.h"
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
	auto transform = GetComponent<TransformComponent>();
	transform->SetPosition(Vector3(0.0f, 500.0f, 100.0f));

	auto statusComponent = AddComponent<StatusComponent>();
	statusComponent->Init(Vector3(200, 50, 50), 6, 40);

	InitModel();

	InitSkill();

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
	cameraPos.z++;
	g_camera3D->SetTarget(cameraPos);

}

void Soldier::Render()
{
	m_viewModelComponent->Draw();
}

void Soldier::InitModel()
{
	m_viewModelComponent = AddComponent<ViewModelComponent>();
	m_viewModelComponent->AddAnimation("Assets/Character/Playable/soldier76/animation/V_Idle.tka", true);
	m_viewModelComponent->AddAnimation("Assets/Character/Playable/soldier76/animation/V_AutoShoot.tka", false);
	m_viewModelComponent->AddAnimation("Assets/Character/Playable/soldier76/animation/V_BioticField.tka", false);
	m_viewModelComponent->AddAnimation("Assets/Character/Playable/soldier76/animation/V_Reload.tka", false);
	m_viewModelComponent->AddAnimation("Assets/Character/Playable/soldier76/animation/V_Run.tka", true);
	m_viewModelComponent->AddAnimation("Assets/Character/Playable/soldier76/animation/V_SkillShoot.tka", false);
	m_viewModelComponent->SetModel("Assets/Character/Playable/soldier76/model/soldierViewModel.tkm", true);
	m_viewModelComponent->SetDrawFlag(true);
}

void Soldier::InitSkill()
{
	auto skillsComponent = AddComponent<SkillsComponent>();

	{
		auto skill = std::make_unique<PulseRifle>();
		skill->SetParent(this);
		skillsComponent->SetMainWepon(std::move(skill));
	}
	{
		auto skill = std::make_unique<HelixRocket>();
		skill->SetParent(this);
		skill->Init();
		skillsComponent->SetSkill(std::move(skill), EnSkillNumber::enFastSkill);
	}
	{
		auto skill = std::make_unique<BioticField>();
		skill->SetParent(this);
		skill->Init();
		skillsComponent->SetSkill(std::move(skill), EnSkillNumber::enSecondSkill);
	}
	{
		auto skill = std::make_unique<Sprint>();
		skill->SetParent(this);
		skillsComponent->SetSkill(std::move(skill), EnSkillNumber::enThirdSkill);
	}
}

void Soldier::InitCollider()
{
	auto colliderComponent = AddComponent<ColliderComponent>();
	auto rigidBodyComponent = AddComponent<RigidBodyComponent>();
	auto charactorColliderComponent = AddComponent<CharactorColliderComponent>();

	colliderComponent->CreateCapsule(50, 200);
	colliderComponent->SetCategory(EnCollisionCategory::enCollisionCat_Player);

	rigidBodyComponent->CreateRigidBody();

	charactorColliderComponent->Init();

	AddComponent<CharacterMoveComponent>();

}

void Soldier::InitState()
{
	auto stateControllerComponent = AddComponent<StateControllerComponent>();
	auto stateMachineComponent = AddComponent<StateMachineComponent>();
	auto skillComponent = GetComponent<SkillsComponent>();

	{
		auto state = std::make_unique<IdleState>();
		state->SetOwner(this);
		stateMachineComponent->RegisterMainState(enIdelState, std::move(state));
		stateControllerComponent->RegisterMainState<IdleAIState>(enIdelState);
	}

	{
		auto state = std::make_unique<ReloadState>();
		state->SetWeapon(skillComponent->GetMainWepon());
		stateMachineComponent->RegisterMainState(enReloadState, std::move(state));
		stateControllerComponent->RegisterMainState<ReloadAIState>(enReloadState);
	}

	{
		auto state = std::make_unique<PunchState>();
		//state->SetWeapon(skillComponent->GetMainWepon());
		stateMachineComponent->RegisterMainState(enAttackSkillState, std::move(state));
		stateControllerComponent->RegisterMainState<PunchAIState>(enAttackSkillState);
	}

	{
		auto state = std::make_unique<PulseRifleState>();
		auto aiState = std::make_unique<PulseRifleAIState>();
		state->SetWepon(skillComponent->GetMainWepon());
		aiState->SetWepon(skillComponent->GetMainWepon());
		stateMachineComponent->RegisterMainState(enMainWeaponState, std::move(state));
		stateControllerComponent->RegisterMainState(enMainWeaponState,std::move(aiState));
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

	stateMachineComponent->ResetState();
	stateControllerComponent->ResetState();
}
