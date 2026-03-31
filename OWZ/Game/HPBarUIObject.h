#pragma once
#include <algorithm>
#include "UIObfect.h"
#include"BarUIObject.h"
#include"UIFollowComponent.h"

class HPComponent;

struct HPBarValue
{
	float health = 0.0f;
	float shield = 0.0f;
	float armor = 0.0f;
	float overHealth = 0.0f;

	float maxHealth = 0.0f;
	float maxShield = 0.0f;
	float maxArmor = 0.0f;
	float maxOverHealth = 0.0f;

	float GetTotalMax() const
	{
		return maxHealth + maxShield + maxArmor + maxOverHealth;
	}
};

class PlayerHUDHPBarUI : public ScreenSpaceUIObject
{
private:
	std::weak_ptr<ScreenSpaceUIObject> m_background;
	std::weak_ptr<ScreenSpaceUIObject> m_healthBar;
	std::weak_ptr<ScreenSpaceUIObject> m_shieldBar;
	std::weak_ptr<ScreenSpaceUIObject> m_armorBar;
	std::weak_ptr<ScreenSpaceUIObject> m_overHealthBar;
	std::weak_ptr<ScreenSpaceUIObject> m_frame;

	ScreenUITransformComponent* m_healthTr = nullptr;
	ScreenUITransformComponent* m_shieldTr = nullptr;
	ScreenUITransformComponent* m_armorTr = nullptr;
	ScreenUITransformComponent* m_overHealthTr = nullptr;

	HPComponent* m_hp = nullptr;

	float m_totalWidth = 512.0f;
	float m_height = 64.0f;

public:
	void Init(HPComponent* hp)
	{
		m_hp = hp;

		ScreenSpaceUIObject::Init(); // 親は見た目なし

		AddChildren<ScreenSpaceUIObject>("background");
		AddChildren<ScreenSpaceUIObject>("health");
		AddChildren<ScreenSpaceUIObject>("shield");
		AddChildren<ScreenSpaceUIObject>("armor");
		AddChildren<ScreenSpaceUIObject>("overHealth");
		AddChildren<ScreenSpaceUIObject>("frame");

		m_background = std::dynamic_pointer_cast<ScreenSpaceUIObject>(GetChildren("background"));
		m_healthBar = std::dynamic_pointer_cast<ScreenSpaceUIObject>(GetChildren("health"));
		m_shieldBar = std::dynamic_pointer_cast<ScreenSpaceUIObject>(GetChildren("shield"));
		m_armorBar = std::dynamic_pointer_cast<ScreenSpaceUIObject>(GetChildren("armor"));
		m_overHealthBar = std::dynamic_pointer_cast<ScreenSpaceUIObject>(GetChildren("overHealth"));
		m_frame = std::dynamic_pointer_cast<ScreenSpaceUIObject>(GetChildren("frame"));

		auto bg = m_background.lock();
		auto hpBar = m_healthBar.lock();
		auto shBar = m_shieldBar.lock();
		auto arBar = m_armorBar.lock();
		auto ohBar = m_overHealthBar.lock();
		auto frame = m_frame.lock();

		if (!bg || !hpBar || !shBar || !arBar || !ohBar || !frame) {
			return;
		}

		// 画像は色ごとに別DDS
		bg->Init("Assets/UI/hp_bar_bg.dds", m_totalWidth, m_height);
		hpBar->Init("Assets/UI/hp_bar_fill_health.dds", m_totalWidth, m_height);
		shBar->Init("Assets/UI/hp_bar_fill_shield.dds", m_totalWidth, m_height);
		arBar->Init("Assets/UI/hp_bar_fill_armor.dds", m_totalWidth, m_height);
		ohBar->Init("Assets/UI/hp_bar_fill_overhealth.dds", m_totalWidth, m_height);
		frame->Init("Assets/UI/hp_bar_frame.dds", m_totalWidth, m_height);

		auto bgTr = bg->GetComponent<ScreenUITransformComponent>();
		auto hpTr = hpBar->GetComponent<ScreenUITransformComponent>();
		auto shTr = shBar->GetComponent<ScreenUITransformComponent>();
		auto arTr = arBar->GetComponent<ScreenUITransformComponent>();
		auto ohTr = ohBar->GetComponent<ScreenUITransformComponent>();
		auto frameTr = frame->GetComponent<ScreenUITransformComponent>();

		if (!bgTr || !hpTr || !shTr || !arTr || !ohTr || !frameTr) {
			return;
		}

		m_healthTr = hpTr.get();
		m_shieldTr = shTr.get();
		m_armorTr = arTr.get();
		m_overHealthTr = ohTr.get();

		// 左端基準
		bgTr->SetPivot({ 0.0f, 0.5f });
		hpTr->SetPivot({ 0.0f, 0.5f });
		shTr->SetPivot({ 0.0f, 0.5f });
		arTr->SetPivot({ 0.0f, 0.5f });
		ohTr->SetPivot({ 0.0f, 0.5f });
		frameTr->SetPivot({ 0.0f, 0.5f });

		bgTr->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
		hpTr->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
		shTr->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
		arTr->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
		ohTr->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
		frameTr->SetLocalPosition({ 0.0f, 0.0f, 0.0f });

		bgTr->SetScale({ m_totalWidth, m_height, 1.0f });
		frameTr->SetScale({ m_totalWidth, m_height, 1.0f });

		auto rootTr = GetComponent<ScreenUITransformComponent>();
		if (rootTr) {
			rootTr->SetLocalPosition({ 50.0f, -300.0f, 0.0f });
		}

		HPBarValue initValue{};
		UpdateBars(initValue);
	}

	void Update() override
	{
		ScreenSpaceUIObject::Update();

		// ここは仮
		// 実際には m_hp から現在値/最大値を作る
		HPBarValue value;

		if (m_hp != nullptr) {
			// value.health = m_hp->GetHealth();
			// value.shield = m_hp->GetShield();
			// value.armor = m_hp->GetArmor();
			// value.overHealth = m_hp->GetOverHealth();
			// value.maxHealth = m_hp->GetMaxHealth();
			// value.maxShield = m_hp->GetMaxShield();
			// value.maxArmor = m_hp->GetMaxArmor();
			// value.maxOverHealth = m_hp->GetMaxOverHealth();
		}

		UpdateBars(value);
	}

private:
	void UpdateBars(const HPBarValue& value)
	{
		const float totalMax = value.GetTotalMax();
		if (totalMax <= 0.0f) {
			SetBarTransform(m_healthTr, 0.0f, 0.0f);
			SetBarTransform(m_shieldTr, 0.0f, 0.0f);
			SetBarTransform(m_armorTr, 0.0f, 0.0f);
			SetBarTransform(m_overHealthTr, 0.0f, 0.0f);
			return;
		}

		// 各バーの「現在の見た目幅」
		const float healthWidth =
			m_totalWidth * Clamp(value.health / totalMax);
		const float shieldWidth =
			m_totalWidth * Clamp(value.shield / totalMax);
		const float armorWidth =
			m_totalWidth * Clamp(value.armor / totalMax);
		const float overHealthWidth =
			m_totalWidth * Clamp(value.overHealth / totalMax);

		// 左から順に並べる
		float x = 0.0f;

		SetBarTransform(m_healthTr, x, healthWidth);
		x += healthWidth;

		SetBarTransform(m_shieldTr, x, shieldWidth);
		x += shieldWidth;

		SetBarTransform(m_armorTr, x, armorWidth);
		x += armorWidth;

		SetBarTransform(m_overHealthTr, x, overHealthWidth);
	}

	void SetBarTransform(ScreenUITransformComponent* tr, float leftX, float width)
	{
		if (tr == nullptr) {
			return;
		}

		tr->SetLocalPosition({ leftX, 0.0f, 0.0f });
		tr->SetScale({ width, m_height, 1.0f });
	}

	float Clamp(float v) const
	{
		if (v < 0.0f) {
			return 0.0f;
		}
		if (v > 1.0f) {
			return 1.0f;
		}
		return v;
	}
};

class Enemy;
class EnemyHpBarUI : public WorldSpaceUIObject
{
private:
	//std::weak_ptr<Enemy> m_enemy;//NOTE:エネミーがまだないのでコメントアウト
	std::weak_ptr<WorldSpaceBarUI> m_bar;

	Vector3 m_offset = { 0.0f, 120.0f, 0.0f }; // 頭上オフセット

public:
	void Init(const std::shared_ptr<GameObject>& enemy)
	{
		WorldSpaceUIObject::Init(); // 親は見た目なし
		/*m_enemy = enemy;*/

		AddChildren<WorldSpaceBarUI>("hpBar");
		auto bar = std::dynamic_pointer_cast<WorldSpaceBarUI>(GetChildren("hpBar"));
		m_bar = bar;

		if (!bar) {
			return;
		}

		bar->Init(
			"Assets/ui/hp/hpbar_bg.DDS",
			"Assets/ui/hp/hpbar_fill.DDS",
			"Assets/ui/hp/hpbar_frame.DDS",
			80.0f,
			10.0f
		);
		bar->SetRate(1.0f);

		AddComponent<WorldUIFollowComponent>(enemy, m_offset);
	}

	void Update() override
	{
		//NOTE:エネミーがまだないのでコメントアウト
		//NOTE:エネミーがまだないのでコメントアウト

		//auto enemy = m_enemy.lock();
		//auto bar = m_bar.lock();

		//if (!enemy) {
		//	RequestDestroy();
		//	return;
		//}

		//// 敵が死んだら消える
		//if (enemy->IsDead()) {
		//	RequestDestroy();
		//	return;
		//}


		//if (!bar) {
		//	return;
		//}

		//// HP割合更新
		//float maxHp = static_cast<float>(enemy->GetMaxHp());
		//float hp = static_cast<float>(enemy->GetHp());

		//float rate = 0.0f;
		//if (maxHp > 0.0f) {
		//	rate = hp / maxHp;
		//}
		//bar->SetRate(rate);

	}
};