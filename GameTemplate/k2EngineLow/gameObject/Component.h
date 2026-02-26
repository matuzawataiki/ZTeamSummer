#pragma once
namespace nsK2EngineLow
{
	class Component : public Noncopyable
	{
	private:
		IGameObject* m_owner = nullptr;

		bool m_isActive = false;
		bool m_isStart = false;

	public:
		virtual ~Component() = default;
		virtual bool Start() {}
		virtual void Update() {}

		void OnActive() { m_isActive = true; }
		void OffActive() { m_isActive = false; }
		bool IsActive() { return m_isActive; }

		void OnActive() { m_isStart = true; }
		bool IsActive() { return m_isStart; }
	};

}
