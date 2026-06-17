#include "stdafx.h"
#include "NumberDisplayUIObject.h"
#include "NumberSlotUIObject.h"
#include "UITransform.h"

void NumberDisplayUIBaseObject::SetValue(int value)
{

	// 数字を表示できる範囲に収める
	{
		// 表示できる最大値を超えていたら最大値にする。
		int maxValue = 1;
		for (int i = 0; i < m_slotCount; ++i) {
			maxValue *= 10;
		}
		maxValue -= 1;

		if (value > maxValue) {
			value = maxValue;
		}

		if (value < 0) {
			value = 0;
		}
		m_value = value;
	}

	//ナンバースロットに数字をセット
	{
		int temp = value;

		// 右から数字を入れる
		for (int i = m_slotCount - 1; i >= 0; --i) {
			int number = temp % 10;
			temp /= 10;

			if (m_slots[i]) {
				m_slots[i]->SetNumber(number);
			}
		}
	}

	// 先頭の0を非表示にする
	{
		bool nonZeroFound = false;

		for (int i = 0; i < m_slotCount; ++i) {
			if (!m_slots[i]) {
				continue;
			}

			int number = m_slots[i]->GetCurrentNumber();

			//0じゃないなら表示
			if (number != 0) {
				nonZeroFound = true;
			}


			//0じゃない場合もしくは最後の位の0なら表示する。
			if (nonZeroFound || i == m_slotCount - 1) {
				m_slots[i]->SetVisible(true);
			}
			else {
				m_slots[i]->SetVisible(false);
			}
		}
	}

}

void ScreenNumberDisplayUIObject::Init(int slotCount, float slotWidth, float slotHeight, float spacing)
{
	// 親自身は見た目なし
	UIObject::Init();

	//トランスフォームをセット
	AddComponent<ScreenUITransformComponent>();

	// スロット数は1以上にする
	if (slotCount <= 0) {
		m_slotCount = 1;
	}
	else {
		m_slotCount = slotCount;
	}

	m_slots.clear();

	for (int i = 0; i < m_slotCount; ++i) {

		// 子オブジェクトを作成
		std::string childName = "slot_" + std::to_string(i);
		AddChildren<ScreenNumberSlotUIObject>(childName.c_str());

		// 子オブジェクトを取得
		auto slot = static_cast<ScreenNumberSlotUIObject*>(GetChildren(childName.c_str()));
		if (!slot) {
			continue;
		}

		// 子オブジェクトを初期化
		slot->Init(slotWidth, slotHeight);

		// 子オブジェクトの位置を設定
		auto trans = slot->GetComponent<ScreenUITransformComponent>();
		if (trans) {
			trans->SetLocalPosition({ i * (slotWidth + spacing), 0.0f, 0.0f });
		}

		// 子オブジェクトをスロットリストに追加
		m_slots.push_back(slot);
	}

	SetValue(0);
}

void WorldNumberDisplayUIObject::Init(int slotCount, float slotWidth, float slotHeight, float spacing)
{
	// 親自身は見た目なし
	UIObject::Init();

	//トランスフォームをセット
	AddComponent<WorldUITransformComponent>();

	// スロット数は1以上にする
	if (slotCount <= 0) {
		m_slotCount = 1;
	}
	else {
		m_slotCount = slotCount;
	}

	m_slots.clear();

	for (int i = 0; i < m_slotCount; ++i) {

		// 子オブジェクトを作成
		std::string childName = "slot_" + std::to_string(i);
		AddChildren<WorldNumberSlotUIObject>(childName.c_str());

		// 子オブジェクトを取得
		auto slot = static_cast<WorldNumberSlotUIObject*>(GetChildren(childName.c_str()));
		if (!slot) {
			continue;
		}

		// 子オブジェクトを初期化
		slot->Init(slotWidth, slotHeight);

		// 子オブジェクトの位置を設定
		auto trans = slot->GetComponent<WorldUITransformComponent>();
		if (trans) {
			trans->SetLocalPosition({ i * (slotWidth + spacing), 0.0f, 0.0f });
		}

		// 子オブジェクトをスロットリストに追加
		m_slots.push_back(slot);
	}

	SetValue(0);
}
