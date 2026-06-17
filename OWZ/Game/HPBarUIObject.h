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
	ScreenSpaceUIObject* m_background = nullptr;
	ScreenSpaceUIObject* m_healthBar = nullptr;
	ScreenSpaceUIObject* m_shieldBar = nullptr;
	ScreenSpaceUIObject* m_armorBar = nullptr;
	ScreenSpaceUIObject* m_overHealthBar = nullptr;
	ScreenSpaceUIObject* m_frame = nullptr;

	ScreenUITransformComponent* m_healthTr = nullptr;
	ScreenUITransformComponent* m_shieldTr = nullptr;
	ScreenUITransformComponent* m_armorTr = nullptr;
	ScreenUITransformComponent* m_overHealthTr = nullptr;

	HPComponent* m_hp = nullptr;

	float m_totalWidth = 512.0f;
	float m_height = 64.0f;

public:
	void Init(HPComponent* hp);

	void Update() override;

private:
	void UpdateBars(const HPBarValue& value);

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

class DummyEnemy;
class EnemyHpBarUI : public WorldSpaceUIObject
{
private:
	DummyEnemy* m_enemy = nullptr;
	WorldSpaceBarUI* m_bar = nullptr;

	Vector3 m_offset = { 0.0f, 120.0f, 0.0f }; // 頭上オフセット

public:
	void Init(DummyEnemy* enemy);

	void Update() override;
};