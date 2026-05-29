#include "stdafx.h"
#include "StageObject.h"
#include "Component/Graphics/ModelComponent.h"
#include "Component/Collision/ColliderComponent.h"
#include "Component/Collision/RigidBodyComponent.h"

bool StageObject::Start()
{

	return true;
}

void StageObject::Init(Vector3 position, Quaternion rotetion)
{
	m_model = AddComponent<ModelComponent>();
	auto collider = AddComponent<ColliderComponent>();
	auto rigidBody = AddComponent<RigidBodyComponent>();

	m_model->SetModel("Assets/target/stage.tkm");

	collider->CreateMesh(m_model->GetModel(), m_model->GetModel().GetWorldMatrix(), Vector3(29000, 10000.0f, 0.0f));
	collider->SetCategory(EnCollisionCategory::enCollisionCat_Environment);
	collider->SetCategoryMask(EnCollisionCategory::enCollisionCat_None);
	rigidBody->CreateRigidBody();

	auto trans = GetComponent<TransformComponent>();
	trans->SetPosition(position);
	trans->SetRotation(rotetion);
}

void StageObject::Render()
{
}
