#pragma once
#include "BarUIObject.h"

class HPComponent;

class PlayerHUDHPBarUI : public ScreenSpaceBarUI
{
private:
	//TODO:今はHPがないのでコメントアウトしている
	//HPComponent* m_hp = nullptr;

public:
	void Init(HPComponent* hp)
	{
		//m_hp = hp;

		ScreenSpaceBarUI::Init(
			"Assets/UI/hp_bar_bg.dds",
			"Assets/UI/hp_bar_fill.dds",
			"Assets/UI/hp_bar_frame.dds",
			512.0f,
			64.0f
		);

		auto tr = GetComponent<ScreenUITransformComponent>();
		if (tr) {
			tr->SetLocalPosition({ 50.0f, -300.0f, 0.0f });
		}
	}

	void Update() override
	{
		ScreenSpaceBarUI::Update();

		//TODO:今はHPがないのでコメントアウトしている
		//if (m_hp == nullptr) {
		//	return;
		//}

		//const float maxHp = m_hp->GetMaxHP();
		//if (maxHp <= 0.0f) {
		//	SetRate(0.0f);
		//	return;
		//}

		//SetRate(m_hp->GetCurrentHP() / maxHp);
	}
};
