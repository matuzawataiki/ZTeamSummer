#include "stdafx.h"
#include "RigidBodyComponent.h"
#include "Component/Collision/ColliderComponent.h"


RigidBodyComponent::RigidBodyComponent() = default;

RigidBodyComponent::~RigidBodyComponent()
{
	// RigidBody::~RigidBody() が PhysicsWorld から自動的に削除する
}

bool RigidBodyComponent::Start()
{
	return true;
}

void RigidBodyComponent::Update()
{
	if (m_isCreated) {
		SyncToTransform();
	}
}

void RigidBodyComponent::CreateRigidBody(float mass, float restitution)
{
	auto transform = GetComponent<TransformComponent>();
	auto collider = GetComponent<ColliderComponent>();
	collider->Deactivate();

	RigidBodyInitData initData;
	initData.pos = transform->GetPosition();
	initData.rot = transform->GetRotation();
	initData.collider = collider->GetGhostObject().GetCollider();
	initData.mass = mass;
	initData.restitution = restitution;

	m_rigidBody.Init(initData);
	m_isCreated = true;
}

void RigidBodyComponent::AddForce(const Vector3& force, const Vector3& relPos)
{
	if (!m_isCreated) return;
	m_rigidBody.AddForce(force, relPos);
}

void RigidBodyComponent::SetLinearVelocity(const Vector3& velocity)
{
	if (!m_isCreated) return;
	m_rigidBody.SetLinearVelocity(velocity);
}

Vector3 RigidBodyComponent::GetLinearVelocity() const
{
	if (!m_isCreated) return Vector3::Zero;
	return m_rigidBody.GetLinearVelocity();
}

void RigidBodyComponent::SetAngularVelocity(const Vector3& velocity)
{
	if (!m_isCreated) return;
	m_rigidBody.SetAngularVelocity(velocity);
}

void RigidBodyComponent::SetLinearFactor(float x, float y, float z)
{
	if (!m_isCreated) return;
	m_rigidBody.SetLinearFactor(x, y, z);
}

void RigidBodyComponent::SetAngularFactor(float x, float y, float z)
{
	if (!m_isCreated) return;
	Vector3 v = { x, y, z };
	m_rigidBody.SetAngularFactor(v);
}

void RigidBodyComponent::SetFriction(float friction)
{
	if (!m_isCreated) return;
	m_rigidBody.SetFriction(friction);
}

void RigidBodyComponent::SyncToTransform()
{
	auto transform = GetComponent<TransformComponent>();
	if (transform == nullptr) return;

	Vector3 pos;
	Quaternion rot;
	m_rigidBody.GetPositionAndRotation(pos, rot);
	transform->SetPosition(pos);
	transform->SetRotation(rot);
}

void RigidBodyComponent::SyncFromTransform()
{
	auto transform = GetComponent<TransformComponent>();
	if (transform == nullptr) return;

	m_rigidBody.SetPositionAndRotation(
		transform->GetPosition(),
		transform->GetRotation()
	);
}
