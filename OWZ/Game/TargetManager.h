#pragma once

class StageObject;
class TargetBase;
class TargetManager : public Noncopyable
{
private:
	TargetManager();
	~TargetManager();
	static TargetManager* m_instance;

private:
	std::vector<std::unique_ptr<TargetBase>> m_targets;
	std::unique_ptr<StageObject> m_stage;
	int m_currentPoint = 0;
	LevelRender m_mapLevel;
public:

	void Init();

	void Update();

	int GetPoint() { return m_currentPoint; }

	void AddPoint(int point) { m_currentPoint += point; }


	static void CreateInstance() {
		if (!m_instance) {
			m_instance = new TargetManager;
		}
	}
	static void DeleteInstance() {
		delete m_instance;
		m_instance = nullptr;
	}
	static TargetManager* GetInstance() {
		return m_instance;
	}
};

