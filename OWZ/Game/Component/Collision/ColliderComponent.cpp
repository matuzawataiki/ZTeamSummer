#include "stdafx.h"
#include "ColliderComponent.h"

ColliderComponent::ColliderComponent() = default;

ColliderComponent::~ColliderComponent() 
{
	if (m_isCreated) {
		CollisionManager::GetInstance()->Unregister(this);
	}
}

bool ColliderComponent::Start()
{
	return true;
}

void ColliderComponent::Update()
{
	auto transform = GetComponent<TransformComponent>();

	m_ghostObject.SetPosition(transform->GetPosition());
	m_ghostObject.SetRotation(transform->GetRotation());
}

void ColliderComponent::CreateBox(const Vector3& size)
{
	TransformComponent* transform = GetComponent<TransformComponent>();

	Vector3 position = transform->GetPosition();
	Quaternion rotation = transform->GetRotation();

	m_ghostObject.CreateBox(position, rotation, size);
	m_radius = max(size.x, size.z) / 2;
	m_height = size.y;
	m_isCreated = true;

	CollisionManager::GetInstance()->Register(this);
}

void ColliderComponent::CreateSphere(float radius)
{
	TransformComponent* transform = GetComponent<TransformComponent>();

	Vector3 position = transform->GetPosition();
	Quaternion rotation = transform->GetRotation();


	m_ghostObject.CreateSphere(position, rotation, radius);
	m_radius = radius;
	m_height = radius;
	m_isCreated = true;

	CollisionManager::GetInstance()->Register(this);
}

void ColliderComponent::CreateCapsule(float radius, float height)
{
	TransformComponent* transform = GetComponent<TransformComponent>();

	Vector3 position = transform->GetPosition();
	Quaternion rotation = transform->GetRotation();

	m_ghostObject.CreateCapsule(position, rotation, radius, height);
	m_radius = radius;
	m_height = height;
	m_isCreated = true;

	CollisionManager::GetInstance()->Register(this);
}

void ColliderComponent::CreateMesh(const Model& model, const Matrix& worldMatrix, const Vector3& size)
{
	TransformComponent* transform = GetComponent<TransformComponent>();

	Vector3 position = transform->GetPosition();
	Quaternion rotation = transform->GetRotation();

	m_ghostObject.CreateMesh(position, rotation, model, worldMatrix);

	m_radius = max(size.x, size.z) / 2;
	m_height = size.y;

	CollisionManager::GetInstance()->Register(this);
}

void ColliderComponent::SyncTransform()
{
	auto transform = GetComponent<TransformComponent>();
	if (transform == nullptr) {
		return;
	}
	m_ghostObject.SetPosition(transform->GetPosition());
	m_ghostObject.SetRotation(transform->GetRotation());
}
