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
		GameObject* m_owner;

		bool m_isActive = false;
		bool m_isStart = false;

	public:
		virtual ~Component() = default;

		void UpdateWrapper();

		void Active() { m_isActive = true; }
		void Deactivate() { m_isActive = false; }
		bool IsActive() { return m_isActive; }

		void OnStart() { m_isStart = true; }
		bool IsStart() { return m_isStart; }

		void SetOwner(GameObject* gameObject) {
			m_owner = gameObject;
		}
		GameObject* GetOwner() {
			return m_owner;
		}

	private:
		virtual bool Start() { return true; }
		virtual void Update() {}
	};
}
