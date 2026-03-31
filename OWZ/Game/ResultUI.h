#pragma once
#include "UIObfect.h"

class ScreenSpaceUIObject;
class ScreenUITransformComponent;

enum class ResultType
{
	None,
	Victory,
	Defeat
};

class ResultUI : public ScreenSpaceUIObject
{
private:
	std::weak_ptr<ScreenSpaceUIObject> m_resultText;

	ResultType m_resultType = ResultType::None;
	bool m_isShown = false;

public:
	void Init();

	void ShowVictory();
	void ShowDefeat();
	void Hide();
	void Render() override;

	void Update() override {
	}

	bool IsShown() const
	{
		return m_isShown;
	}

	ResultType GetResultType() const
	{
		return m_resultType;
	}

private:
	void SetChildrenVisible(bool isVisible);
	void SetSprite(
		const std::shared_ptr<ScreenSpaceUIObject>& ui,
		const char* filePath,
		float width,
		float height);
	/// <summary>
	/// 結果テキストのスケールアニメーションを再生する。
	/// </summary>
	void PlayAnimation();
};