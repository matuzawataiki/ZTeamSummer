#include "stdafx.h"
#include "Punch.h"
#include "Component/Collision/ColliderComponent.h"
#include "Component/Status/StatusComponent.h"

bool Punch::Start()
{
    auto transformComponent = AddComponent<TransformComponent>();
    auto colliderComponent = AddComponent<ColliderComponent>();

    transformComponent->SetParent(m_parent->GetComponent<TransformComponent>()->GetTransform());

    colliderComponent->CreateSphere(50.0f);
    colliderComponent->SetCategory(enCollisionCat_PlayerBullet);
    colliderComponent->SetCategoryMask(EnCollisionCategory::enCollisionCat_Enemy);
    colliderComponent->SetOnHitCallback([this](const HitResult& result) {
        this->Hit(result);
        });
    colliderComponent->Deactivate();
    return true;
}

void Punch::Update()
{
	if (m_activeFlag) {
		m_activeFlag = false;
		GetComponent<ColliderComponent>()->Deactivate();
	}

	if (m_fierFlag) {
		m_fierFlag = false;
		m_activeFlag = true;
	}
}

void Punch::Fire()
{
	GetComponent<ColliderComponent>()->Active();
	m_fierFlag = true;
}

void Punch::Hit(const HitResult& hitResult)
{
	auto transformComponent = GetComponent<TransformComponent>();
	auto hitTransform = hitResult.hitObject->GetComponent<TransformComponent>();

	Vector3 blastToEnemy = hitTransform->GetPosition() - transformComponent->GetPosition();
	Vector3 targetDirection = blastToEnemy;
	targetDirection.Normalize();

	HitResult raycastResult;
	CollisionManager::GetInstance()->Raycast(
		transformComponent->GetPosition(),
		targetDirection,
		200,
		raycastResult,
		EnCollisionCategory::enCollisionCat_Enemy || EnCollisionCategory::enCollisionCat_Environment
	);

	if (hitResult.hitObject != raycastResult.hitObject) { return; }

	hitResult.hitObject->GetComponent<StatusComponent>()->GetHP()->AddDamege(40);
}
