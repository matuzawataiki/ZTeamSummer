#pragma once
class SceneManager;
class GameManager : public Noncopyable
{
public:
	GameManager();
	~GameManager();

private:
	std::unique_ptr<SceneManager> m_sceneManager;

public:
	void Update();
	void Draw();
	
};

