#pragma once
namespace nsK2EngineLow
{
	class GameObject : public Noncopyable
	{
	public:
		virtual ~GameObject()
		{
		}
	public:
		virtual bool Start() { return true; }
		virtual void Update() {}
		virtual void Render(){}

	public:
		bool IsStart() const {return m_isStart;}
		bool IsActive() const {return m_isActive;}

		void Activate() {m_isActive = true;}
		void Deactivate() {m_isActive = false;}

	public:
		void UpdateWrapper()
		{
			if (m_isActive && m_isStart) {
				Update();
				for (auto component : m_componentList) {
					component.second->UpdateWrapper();
				}
			}
		}

		void StartWrapper()
		{
			if (m_isActive && !m_isStart) {
				if (Start()) {
					//初期化処理完了。
					m_isStart = true;
				}
			}
		}

		template <typename T>
		void AddComponent() {
			T* component = new T;
			m_componentList.emplace(T::ID(), component);
		}


		friend class CGameObjectManager;
	protected:
		bool m_isStart = false;							//Startの開始フラグ。
		bool m_isActive = true;							//Activeフラグ。

		std::unordered_map<uint32_t, Component*> m_componentList;
	};

}
