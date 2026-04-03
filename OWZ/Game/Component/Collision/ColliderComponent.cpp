#include "stdafx.h"
#include "ColliderComponent.h"

ColliderComponent::ColliderComponent() = default;

ColliderComponent::~ColliderComponent() 
{
	if (m_isCreated) {
		auto collicomp = std::dynamic_pointer_cast<ColliderComponent>(shared_from_this());
		CollisionManager::GetInstance()->Unregister(collicomp);
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
	std::shared_ptr<TransformComponent> transform = GetComponent<TransformComponent>();

	Vector3 position = transform->GetPosition();
	Quaternion rotation = transform->GetRotation();

	m_ghostObject.CreateBox(position, rotation, size);
	m_radius = max(size.x, size.z) / 2;
	m_isCreated = true;

	auto collicomp = std::dynamic_pointer_cast<ColliderComponent>(shared_from_this());
	CollisionManager::GetInstance()->Register(collicomp);
}

void ColliderComponent::CreateSphere(float radius)
{
	std::shared_ptr<TransformComponent> transform = GetComponent<TransformComponent>();

	Vector3 position = transform->GetPosition();
	Quaternion rotation = transform->GetRotation();


	m_ghostObject.CreateSphere(position, rotation, radius);
	m_radius = radius;
	m_isCreated = true;

	auto collicomp = std::dynamic_pointer_cast<ColliderComponent>(shared_from_this());
	CollisionManager::GetInstance()->Register(collicomp);
}

void ColliderComponent::CreateCapsule(float radius, float height)
{
	std::shared_ptr<TransformComponent> transform = GetComponent<TransformComponent>();

	Vector3 position = transform->GetPosition();
	Quaternion rotation = transform->GetRotation();

	m_ghostObject.CreateCapsule(position, rotation, radius, height);
	m_radius = radius;
	m_isCreated = true;

	auto collicomp = std::dynamic_pointer_cast<ColliderComponent>(shared_from_this());
	CollisionManager::GetInstance()->Register(collicomp);

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
