#pragma once
#include "Transform.h"
#include "gameObject/Component.h"

namespace nsK2EngineLow
{
	class TransformComponent : public Component
	{
		appClass(TransformComponent);
	public:
		TransformComponent();
		~TransformComponent();

	private:
		std::unique_ptr<Transform> m_transform;

	public:
		Transform* GetTransform() { return m_transform.get(); }
		void SetParent(Transform* parent) { m_transform->SetParent(parent, m_transform.get()); }

		Vector3 GetPosition() { return m_transform->GetPosition(); }
		Vector3 GetLocalPosition() { return m_transform->GetLocalPosition(); }
		void SetPosition(const Vector3& position) { m_transform->SetLocalPosition(position); }
		void AddPosition(const Vector3& position) { m_transform->AddLocalPosition(position); }

		Quaternion GetRotation() { return m_transform->GetRotation(); }
		Quaternion GetLocalRotation() { return m_transform->GetLocalRotation(); }
		void SetRotation(const Quaternion& rotation) { m_transform->SetLocalRotation(rotation); }
		void AddRotation(const Quaternion& rotation) { m_transform->AddLocalRotation(rotation); }

		Vector3 GetScale() { return m_transform->GetScale(); }
		Vector3 GetLocalScale() { return m_transform->GetLocalScale(); }
		void SetScale(const Vector3& scale) { m_transform->SetLocalScale(scale); }
		void AddScale(const Vector3& scale) { m_transform->AddLocalScale(scale); }
	};
}
