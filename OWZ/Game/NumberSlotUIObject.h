#pragma once
#include "UIObfect.h"

class ScreenSpaceUIObject;
class SpriteComponent;

class NumberSlotUIBaseObject : public UIObject
{
protected:
	std::array<std::shared_ptr<UIObject>, 10> m_numberSprites;
	int m_currentNumber = 0;
	bool m_isVisible = true;

protected:
	void RefreshVisible();

	void InitNumberSprites(float width, float height)
	{
		m_numberSprites[0]->Init("Assets/ui/number/num_0.DDS", width, height);
		m_numberSprites[1]->Init("Assets/ui/number/num_1.DDS", width, height);
		m_numberSprites[2]->Init("Assets/ui/number/num_2.DDS", width, height);
		m_numberSprites[3]->Init("Assets/ui/number/num_3.DDS", width, height);
		m_numberSprites[4]->Init("Assets/ui/number/num_4.DDS", width, height);
		m_numberSprites[5]->Init("Assets/ui/number/num_5.DDS", width, height);
		m_numberSprites[6]->Init("Assets/ui/number/num_6.DDS", width, height);
		m_numberSprites[7]->Init("Assets/ui/number/num_7.DDS", width, height);
		m_numberSprites[8]->Init("Assets/ui/number/num_8.DDS", width, height);
		m_numberSprites[9]->Init("Assets/ui/number/num_9.DDS", width, height);
	}

public:
	virtual ~NumberSlotUIBaseObject() noexcept = default;

	virtual void Init(float width, float height) = 0;

	void SetNumber(int number)
	{
		if (number < 0) {
			number = 0;
		}
		if (number > 9) {
			number = 9;
		}

		m_currentNumber = number;
		RefreshVisible();
	}

	void SetVisible(bool isVisible)
	{
		m_isVisible = isVisible;
		RefreshVisible();
	}

	int GetCurrentNumber() const
	{
		return m_currentNumber;
	}
};

/// <summary>
/// スクリーンスペースUIの数字スロットUIオブジェクト
/// </summary>
class ScreenNumberSlotUIObject : public NumberSlotUIBaseObject
{
public:
	void Init(float width, float height) override;
};

/// <summary>
/// worldスペースのUIの数字スロットUIオブジェクト
/// </summary>
class WorldNumberSlotUIObject : public NumberSlotUIBaseObject
{
public:
	void Init(float width, float height) override;
};