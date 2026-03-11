#pragma once
class SceneManager;
class SceneBase : public Noncopyable
{
public:
	SceneBase();
	virtual ~SceneBase();

	/**
	 * @brief 初期化関数
	 */
	virtual void Initialize(){}

	/**
	 * @brief 更新関数
	 * @param manager 
	 */
	virtual void Update(SceneManager& manager) = 0;

	/**
	 * @brief 描画関数
	 */
	virtual void Draw() = 0;

	/**
	 * @brief 終了関数
	 */
	virtual void Finalize(){}
};

