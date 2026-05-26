#include "stdafx.h"
#include "StageObject.h"
#include "Component/Graphics/ModelComponent.h"
#include "Component/Collision/ColliderComponent.h"
#include "Component/Collision/RigidBodyComponent.h"

bool StageObject::Start()
{
	m_model = AddComponent<ModelComponent>();
	auto collider = AddComponent<ColliderComponent>();
	auto rigidBody = AddComponent<RigidBodyComponent>();

	m_model->SetModel("Assets/stage/map.tkm");

	collider->CreateMesh(m_model->GetModel(), m_model->GetModel().GetWorldMatrix(), Vector3(16000.0, 0.0f, 0.0f));
	collider->SetCategory(EnCollisionCategory::enCollisionCat_Environment);
	rigidBody->CreateRigidBody();

	auto trans = GetComponent<TransformComponent>();

	return true;
}
