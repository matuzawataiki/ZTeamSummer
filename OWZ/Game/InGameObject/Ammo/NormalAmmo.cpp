#include "stdafx.h"
#include "NormalAmmo.h"
#include "Component/Math/Transform.h"
#include "Component/Collision/ColliderComponent.h"
#include "Component/Skill/WeaponData.h"
#include "Component/Graphics/ModelComponent.h"

void NormalAmmo::Init(AmmoData ammoData)
{
	AddComponent<TransformComponent>();
	AddComponent<ModelComponent>();
	AddComponent<ColliderComponent>();

	m_speed = ammoData.speed;
	m_isProjectile = ammoData.isProjectile;

	auto colliderComponent = GetComponent<ColliderComponent>();
	colliderComponent->CreateSphere(ammoData.radius);

	auto modelComponent = GetComponent<ModelComponent>();
	modelComponent->SetModel(ammoData.modelFilePath.c_str());


}

void NormalAmmo::GoAmmo(Vector3 moveDirection, Vector3 position)
{
	m_moveDirectiron = moveDirection;
	auto transfomComponent = GetComponent<TransformComponent>();
	Quaternion rot;
	rot.SetRotationDegX(m_moveDirectiron.x);
	rot.SetRotationDegY(m_moveDirectiron.y);
	rot.SetRotationDegZ(m_moveDirectiron.z);
	transfomComponent->SetPosition(position);
	transfomComponent->SetRotation(rot);
}

void NormalAmmo::Update()
{
	auto transfomComponent = GetComponent<TransformComponent>();

	Vector3 move = m_moveDirectiron * m_speed;
	transfomComponent->AddPosition(move);
}
