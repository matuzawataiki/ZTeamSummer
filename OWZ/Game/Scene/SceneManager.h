#pragma once

class SceneBase;
class SceneManager : public Noncopyable
{
private:
	std::unique_ptr<SceneBase> m_currentScene;	//現在のシーン
	std::unique_ptr<SceneBase> m_nextScene;		//次のシーン

public:
	SceneManager();
	~SceneManager();

	/**
	 * @brief 次のシーンをセット
	 * @param scene 
	 */
	template <typename T>
	void ChangeScene() {
		m_nextScene = std::make_unique<T>();
	}

	/**
	 * @brief 更新処理
	 */
	void Update();

	/**
	 * @brief 描画処理
	 */
	void Draw();
};

