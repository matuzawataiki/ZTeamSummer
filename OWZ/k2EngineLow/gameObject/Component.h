#pragma once
#include "util/CRC32.h"

#define appClass(name)	\
public:\
	static constexpr uint32_t ID() { return Hash32(#name); }

namespace nsK2EngineLow
{
	class IGameObject;
	class Component : public Noncopyable
	{
	protected:
		IGameObject* m_owner = nullptr;

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

		void SetOwner(IGameObject* gameObject) {
			m_owner = gameObject;
		}

	private:
		virtual bool Start() { return true; }
		virtual void Update() {}
	};
}
