#pragma once
#include "Scene/SceneBase.h"
class SceneManager
{
private:
	std::unique_ptr<SceneBase> m_currentScene;
	std::unique_ptr<SceneBase> m_nextScene;
};

