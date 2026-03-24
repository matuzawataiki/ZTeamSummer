#pragma once
namespace nsK2EngineLow
{
	class GameObject : public Noncopyable, public std::enable_shared_from_this<GameObject>
	{
	public:
		virtual ~GameObject()
		{
		}
	public:
		virtual bool Start() { return true; }
		virtual void Update() {}
		virtual void Render() {}

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

		template <typename T, class... Args>
		void AddComponent(Args&&... args) {
			std::shared_ptr<T> t = std::make_shared<T>(std::forward<Args>(args)...);
			t->SetOwner(shared_from_this());
			t->OnActive();
			m_componentList.emplace(T::ID(), t);

		}
		template <typename T>
		std::shared_ptr<T> GetComponent() {
			std::shared_ptr<Component> c = m_componentList.find(T::ID())->second;
			return std::dynamic_pointer_cast<T>(c);
		}

		template <typename T, class... Args>
		void AddChildren(std::string name, Args&&... args) {
			std::shared_ptr<GameObject > gameObject = std::make_shared<T>(std::forward<Args>(args)...);
			m_children.emplace(name, gameObject);
		}

		void SetParent(std::shared_ptr<GameObject> gameObject) {
			m_parent = gameObject;
		}
		std::shared_ptr<GameObject> GetParent() {
			return m_parent.lock();
		}

		void SetChildren(std::string name, std::shared_ptr<GameObject> gameObject) {
			m_children.emplace(name,gameObject);
		}
		std::shared_ptr<GameObject> GetChildren(std::string name) {
			return m_children.find(name)->second;
		}

	protected:
		bool m_isStart = false;							//Startの開始フラグ。
		bool m_isActive = true;							//Activeフラグ。

		std::weak_ptr<GameObject> m_parent;
		std::unordered_map <std::string, std::shared_ptr<GameObject>> m_children;

		std::unordered_map <uint32_t, std::shared_ptr<Component>> m_componentList;
	};

}
