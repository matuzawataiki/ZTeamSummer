#pragma once
namespace nsK2EngineLow {


	class UITransformBase :Component
	{
	protected:
		bool m_isDirty = true;

	public:
		virtual ~UITransformBase() = default;
		virtual void UpdateTransform() = 0;
	};

	class WorldUITransformComponent :UITransformBase
	{
	private:
		Vector3    m_position = Vector3::Zero;
		Quaternion m_rotation = Quaternion::Identity;
		Vector3    m_scale = { 1.0f, 1.0f, 1.0f };
		Vector2    m_pivot = { 0.5f, 0.5f };



		WorldUITransformComponent* m_parent = nullptr;
		std::vector<WorldUITransformComponent*> m_children;

		Vector2 m_worldPosition = Vector2::Zero;

	public:
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
			m_isDirty = true;
		}

		void SetScale(const Vector3& size)
		{
			m_scale = size;
			m_isDirty = true;
		}

		void SetParent(WorldUITransformComponent* parent)
		{
			m_parent = parent;
			m_isDirty = true;
		}

		void UpdateTransform() override
		{
			if (!m_isDirty) {
				return;
			}

			if (m_parent == nullptr) {
				m_worldPosition = m_position;
			}
			else {
				m_parent->UpdateTransform();
				m_worldPosition = m_parent->m_worldPosition + m_position;
			}

			m_isDirty = false;
		}

		const Vector2& GetWorldPosition() const { return m_worldPosition; }
	};
}

