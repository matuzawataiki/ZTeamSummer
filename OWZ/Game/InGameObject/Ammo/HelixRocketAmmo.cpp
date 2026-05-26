#include "stdafx.h"
#include "HelixRocketAmmo.h"
#include "Component/Collision/ColliderComponent.h"
#include "Component/Collision/CollisionManager.h"
#include "Component/Skill/WeaponData.h"
#include "Component/Graphics/ModelComponent.h"
#include "Component/Status/StatusComponent.h"

HelixRocketAmmo::HelixRocketAmmo() = default;

HelixRocketAmmo::~HelixRocketAmmo() = default;


void HelixBlast::Init(AmmoData ammoData)
{
	AddComponent<ColliderComponent>();

	auto colliderComponent = GetComponent<ColliderComponent>();
	colliderComponent->CreateSphere(200);
	colliderComponent->SetCategory(ammoData.thisCategory);
	colliderComponent->SetCategoryMask(ammoData.targetCategory);
	colliderComponent->SetOnHitCallback([this](const HitResult& result) {
		this->HitAmmo(result);
		});
	colliderComponent->Deactivate();
}

void HelixBlast::HitAmmo(const HitResult& hitResult)
{
	m_isHit = true;

	if (hitResult.hitCategory == EnCollisionCategory::enCollisionCat_Environment) { return; }

	auto transformComponent = GetComponent<TransformComponent>();
	auto hitTransform = hitResult.hitObject->GetComponent<TransformComponent>();

	Vector3 blastToEnemy = hitTransform->GetPosition() - transformComponent->GetPosition();
	Vector3 targetDirection = blastToEnemy;
	targetDirection.Normalize();

	HitResult raycastResult;
	CollisionManager::GetInstance()->Raycast(
		transformComponent->GetPosition(), 
		targetDirection, 
		300, 
		raycastResult,
		EnCollisionCategory::enCollisionCat_Enemy|EnCollisionCategory::enCollisionCat_Environment 
	);

	if (hitResult.hitObject != raycastResult.hitObject) { return; }

	float damage = 30;
	
	float length = blastToEnemy.Length();
	length -= 20;
	length = min(160, length);

	damage += length > 0.001 ? length / 160 * 60 : 60;

	auto hitStatusComponent = hitResult.hitObject->GetComponent<StatusComponent>();
	hitStatusComponent->GetHP()->AddDamege(damage);

}

void HelixBlast::Reset()
{
	m_isHit = false;
	auto collider = GetComponent<ColliderComponent>();
	collider->Deactivate();
}

void HelixRocketAmmo::Init(AmmoData ammoData)
{
	AddComponent<ModelComponent>();

	m_speed = ammoData.speed;
	m_mass = ammoData.mass;

	auto colliderComponent = AddComponent<ColliderComponent>();
	colliderComponent->CreateSphere(ammoData.radius);
	colliderComponent->SetCategory(ammoData.thisCategory);
	colliderComponent->SetCategoryMask(ammoData.targetCategory);
	colliderComponent->SetOnHitCallback([this](const HitResult& result) {
		this->HitAmmo(result);
		});
	colliderComponent->UpdateWrapper();
	colliderComponent->Deactivate();

	auto modelComponent = GetComponent<ModelComponent>();
	modelComponent->SetModel(ammoData.modelFilePath.c_str());

	auto blast = std::make_unique<HelixBlast>();
	m_blast = blast.get();
	AddChildren("HelixBlast",std::move(blast));

	m_blast->Init(ammoData);
	m_blast->UpdateWrapper();
	m_blast->Deactivate();

	m_transform = GetComponent<TransformComponent>();
}

void HelixRocketAmmo::GoAmmo(Vector3 moveDirection, Vector3 position) 
{
	m_moveDirectiron = moveDirection;
	auto transfomComponent = GetComponent<TransformComponent>();
	Quaternion rot;
	rot.SetRotationDegX(m_moveDirectiron.x);
	rot.SetRotationDegY(m_moveDirectiron.y);
	rot.SetRotationDegZ(m_moveDirectiron.z);
	transfomComponent->SetPosition(position);
	transfomComponent->SetRotation(rot);

	auto collider = GetComponent<ColliderComponent>();
	collider->Active();
	collider->UpdateWrapper();
}

void HelixRocketAmmo::Update()
{
	if (m_isHit) {
		if (m_blast->IsHit()) {
			m_isHit = false;
			m_blast->Reset();

			m_blast->Deactivate();
			Deactivate();
		}
	}
	else {
		m_transform->AddPosition(m_moveDirectiron * m_speed * g_gameTime->GetFrameDeltaTime());
	}
}

void HelixRocketAmmo::HitAmmo(const HitResult& hitResult)
{
	if (m_isHit) { return; }

	m_blast->Activate();
	auto blastCollider = m_blast->GetComponent<ColliderComponent>();
	blastCollider->Active();
	m_blast->UpdateWrapper();
	m_isHit = true;

	if (hitResult.hitCategory == EnCollisionCategory::enCollisionCat_Environment) { return; }

	auto model = GetComponent<ModelComponent>();
	model->SetDrawFlag(false);

	auto collider = GetComponent<ColliderComponent>();
	collider->Deactivate();

	auto statusComponent = hitResult.hitObject->GetComponent<StatusComponent>();
	statusComponent->GetHP()->AddDamege(30);


}
