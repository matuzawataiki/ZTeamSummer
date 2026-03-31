#include "stdafx.h"
#include "NumberSlotUIObject.h"

void NumberSlotUIBaseObject::RefreshVisible()
{
	// まず全ての数字スプライトを非表示にする。
	for (int i = 0; i < 10; ++i) {
		auto sprite = m_numberSprites[i]->GetComponent<SpriteComponent>();
		if (sprite) {
			sprite->SetVisible(false);
		}
	}

	if (!m_isVisible) {
		return;
	}

	if (m_currentNumber < 0 || m_currentNumber > 9) {
		return;
	}

	// 現在の数字スプライトを表示する。
	auto sprite = m_numberSprites[m_currentNumber]->GetComponent<SpriteComponent>();
	if (sprite) {
		sprite->SetVisible(true);
	}
}

void ScreenNumberSlotUIObject::Init(float width, float height)
{
	UIObject::Init();
	AddComponent<ScreenUITransformComponent>();

	// 子オブジェクトを作る
	for (int i = 0; i < 10; ++i) {
		std::string childName = "number_" + std::to_string(i);
		AddChildren<ScreenSpaceUIObject>(childName.c_str());

		auto child = std::dynamic_pointer_cast<ScreenSpaceUIObject>(GetChildren(childName.c_str()));
		if (!child) {
			continue;
		}

		m_numberSprites[i] = child;
	}

	// 子オブジェクトのスプライトを初期化
	InitNumberSprites(width, height);

	m_currentNumber = 0;
	m_isVisible = true;
	RefreshVisible();
}

void WorldNumberSlotUIObject::Init(float width, float height)
{
	UIObject::Init();
	AddComponent<WorldUITransformComponent>();

	// 子オブジェクトを作る
	for (int i = 0; i < 10; ++i) {
		std::string childName = "number_" + std::to_string(i);
		AddChildren<WorldSpaceUIObject>(childName.c_str());

		auto child = std::dynamic_pointer_cast<WorldSpaceUIObject>(GetChildren(childName.c_str()));
		if (!child) {
			continue;
		}

		m_numberSprites[i] = child;
	}

	// 子オブジェクトのスプライトを初期化
	InitNumberSprites(width, height);

	m_currentNumber = 0;
	m_isVisible = true;
	RefreshVisible();
}
