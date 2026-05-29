#include "stdafx.h"
#include "TargetBase.h"
#include "Component/Collision/ColliderComponent.h"
#include "TargetManager.h"

void TargetBase::Init(const char* mfilePath, int point, Vector3 position, Quaternion rotation)
{
	auto transform = GetComponent<TransformComponent>();
	transform->SetPosition(position);
	transform->SetRotation(rotation);

	m_model = AddComponent<ModelComponent>();
	m_model->AddAnimation("Assets/target/targetAnima.tka", true);
	m_model->SetModel(mfilePath, true);

	auto cmodel = new ModelRender;
	cmodel->Init("Assets/target/targetCollider.tkm");

	auto collider = AddComponent<ColliderComponent>();
	collider->CreateMesh(cmodel->GetModel(), cmodel->GetModel().GetWorldMatrix(), Vector3::One);

	collider->SetCategory(enCollisionCat_Enemy);
	collider->SetCategoryMask(enCollisionCat_PlayerBullet);
	collider->SetOnHitCallback([this](const HitResult& result) {
		this->Hit(); });
	m_point = point;
	m_isInit = true;
}

void TargetBase::Hit()
{
	auto collider = GetComponent<ColliderComponent>();
	collider->Deactivate();

	m_model->SetDrawFlag(false);

	TargetManager::GetInstance()->AddPoint(m_point);
}
