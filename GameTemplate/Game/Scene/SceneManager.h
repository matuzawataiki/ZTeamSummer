#pragma once
#include "Scene/SceneBase.h"
class SceneManager
{
private:
	std::unique_ptr<SceneBase> m_currentScene;	//現在のシーン
	std::unique_ptr<SceneBase> m_nextScene;		//次のシーン

public:
	/**
	 * @brief 次のシーンをセット
	 * @param scene 
	 */
	void ChangeScene(std::unique_ptr<SceneBase> scene) {
		m_nextScene = std::move(scene);
	}

	/**
	 * @brief 更新処理
	 */
	void Update();

	/**
	 * @brief 描画処理
	 * @param rc 
	 */
	void Draw(RenderContext& rc);
};

