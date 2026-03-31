#pragma once
#include "UITransform.h"

class WorldUIFollowComponent : public Component
{
	appClass(WorldUIFollowComponent);
private:
	std::weak_ptr<GameObject> m_target;
	WorldUITransformComponent* m_transform = nullptr;
	Vector3 m_offset = Vector3::Zero;

public:
	WorldUIFollowComponent(std::weak_ptr<GameObject> target, const Vector3& offset)
		:m_target(target),
		m_offset(offset) {
	};

	void SetTarget(std::weak_ptr<GameObject> target)
	{
		m_target = target;
	}

	void SetOffset(const Vector3& offset)
	{
		m_offset = offset;
	}

	bool Start() override
	{
		auto target = m_target.lock();
		m_transform = GetOwner()->GetComponent<WorldUITransformComponent>().get();

		if (!target || m_transform == nullptr) {
			return false;
		}
		return true;
	}

	void Update() override
	{
		auto target = m_target.lock();
		if (!target || m_transform == nullptr) {
			return;
		}


		auto targetTransform = target->GetComponent<TransformComponent>();
		if (!targetTransform) {
			return;
		}
		const Vector3 pos = targetTransform->GetPosition() + m_offset;

		m_transform->SetLocalPosition(pos);
	}
};