#pragma once
#include "system/Math/Transform.h"

class TransformComponent : public Component
{
	appClass(TransformComponent);
public:
	TransformComponent();
	~TransformComponent();

private:
	std::shared_ptr<Transform> m_transform;

public:
	void SetParent(std::shared_ptr<Transform> parent) { m_transform->SetParent(parent, m_transform); }

	Vector3 GetPosition() { return m_transform->GetPosition(); }
	Vector3 GetLocalPosition() { return m_transform->GetLocalPosition(); }
	void SetPosition(const Vector3& position) { m_transform->SetLocalPosition(position); }

	Quaternion GetRotation() { return m_transform->GetRotation(); }
	Quaternion GetLocalRotation() { return m_transform->GetLocalRotation(); }
	void SetRotation(const Quaternion& rotation) { m_transform->SetLocalRotation(rotation); }

	Vector3 GetScale() { return m_transform->GetScale(); }
	Vector3 GetLocalScale() { return m_transform->GetLocalScale(); }
	void SetScale(const Vector3& scale) { m_transform->SetLocalScale(scale); }
};