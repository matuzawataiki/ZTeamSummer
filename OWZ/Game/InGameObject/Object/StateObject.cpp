#include "stdafx.h"
#include "StateObject.h"
#include "Component/Graphics/ModelComponent.h"
#include "Component/Collision/ColliderComponent.h"
#include "Component/Collision/RigidBodyComponent.h"

bool StageObject::Start()
{
	AddComponent<TransformComponent>();
	m_model = AddComponent<ModelComponent>();
	auto collider = AddComponent<ColliderComponent>();
	auto rigidBody = AddComponent<RigidBodyComponent>();

	m_model->SetModel("Assets/stage/map.tkm");

	collider->CreateMesh(m_model->GetModel(), Matrix::Identity);
	rigidBody->CreateRigidBody();

	return true;
}

void StageObject::Render()
{
	m_model->Draw();
}
