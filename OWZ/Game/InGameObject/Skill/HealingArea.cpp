#include "stdafx.h"
#include "HealingArea.h"
#include "Component/Collision/ColliderComponent.h"
#include "Component/Status/StatusComponent.h"

void HealingArea::Init(float areaSize, float heelHeight)
{
	AddComponent<TransformComponent>();
	auto colliderComponent = AddComponent<ColliderComponent>();
	colliderComponent->CreateSphere(100);
	colliderComponent->SetCategory(EnCollisionCategory::enCollisionCat_Heel);
	colliderComponent->SetCategoryMask(EnCollisionCategory::enCollisionCat_Player);
	colliderComponent->SetOnHitCallback([this](const HitResult& result) {
		this->HitArea(result.hitObject);
		});

}

void HealingArea::HitArea(GameObject* HitObject)
{
	HitObject->GetComponent<StatusComponent>()->GetHP()->AddHeel(m_heelHeight * g_gameTime->GetFrameDeltaTime());
}
