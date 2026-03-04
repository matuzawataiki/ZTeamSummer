#include "stdafx.h"
#include "SceneManager.h"
#include "Scene/SceneBase.h"

SceneManager::~SceneManager()
{
}

void SceneManager::ChangeScene(std::unique_ptr<SceneBase> scene)
{
	m_nextScene = std::move(scene);
}

void SceneManager::Update()
{
	//次のシーンがあれば遷移処理
	if (m_nextScene) {
		if (m_currentScene) {
			m_currentScene->Finalize();
		}
		m_currentScene = std::move(m_nextScene);
		m_currentScene->Initialize();
	}

	//更新処理
	if (m_currentScene) {
		m_currentScene->Update(*this);
	}
}

void SceneManager::Draw(RenderContext& rc)
{
	//描画処理
	if (m_currentScene) {
		m_currentScene->Draw(rc);
	}
}
