#pragma once

class SceneManager;
class SceneBase : public Noncopyable
{
public:
	virtual ~SceneBase() = default;

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
	 * @param rc 
	 */
	virtual void Draw(RenderContext& rc) = 0;

	/**
	 * @brief 終了関数
	 */
	virtual void Finalize(){}
};

