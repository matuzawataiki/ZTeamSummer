#pragma once
#include "util/CRC32.h"

#define appClass(name)	\
public:\
	static constexpr uint32_t ID() { return Hash32(#name); }

namespace nsK2EngineLow
{
	class GameObject;
	class Component : public Noncopyable
	{
	protected:
		std::weak_ptr<GameObject> m_owner;

		bool m_isActive = false;
		bool m_isStart = false;

	public:
		virtual ~Component() = default;

		void UpdateWrapper();

		void OnActive() { m_isActive = true; }
		void OffActive() { m_isActive = false; }
		bool IsActive() { return m_isActive; }

		void OnStart() { m_isStart = true; }
		bool IsStart() { return m_isStart; }

		void SetOwner(std::shared_ptr<GameObject> gameObject) {
			m_owner = gameObject;
		}
		std::shared_ptr<GameObject> GetOwner() {
			return m_owner.lock();
		}

		template <typename T>
		std::shared_ptr<T> GetComponent() {
			return m_owner.lock()->templateGetComponent<T>();
		}

	private:
		virtual bool Start() { return true; }
		virtual void Update() {}
	};
}
