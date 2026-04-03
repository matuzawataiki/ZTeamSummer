#pragma once
class SceneManager;
class GameManager : public Noncopyable
{
public:
	GameManager();
	~GameManager();

private:
	std::unique_ptr<SceneManager> m_sceneManager;
	ModelRender m_bgModel;
	PhysicsStaticObject m_bt;

public:
	void Update();
	void Draw();
	
};

