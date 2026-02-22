#pragma once
#include "Scene/SceneManager.h"


class Game : public IGameObject
{
private:
	std::unique_ptr<SceneManager> m_sceneManager;

public:
	Game() {}
	~Game() {}
	bool Start();
	void Update();
	void Render(RenderContext& rc);
};

