#include "stdafx.h"
#include "GoalObject.h"
#include "Component/Collision/ColliderComponent.h"

void GoalObject::Init()
{
	auto transform = GetComponent<TransformComponent>();
	transform->SetPosition(Vector3(0.0f, 610.0, -20155.0f));

	auto collision = AddComponent<ColliderComponent>();
	collision->CreateSphere(60.0f);
	collision->SetCategory(enCollisionCat_Trigger);
	collision->SetCategoryMask(EnCollisionCategory::enCollisionCat_Player);
	collision->SetOnHitCallback([this](const HitResult& result) {
		this->Hit();
		});

}

void GoalObject::Hit()
{
	m_isHit = true;

}
