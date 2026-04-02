#pragma once
#include "Parameter/General/HealthParameter.h"
#include "gameObject/Component.h"
#include <functional>


class HealthComponent : public Component
{
	appClass(HealthComponent)


public:
	explicit HealthComponent(const HealthParameter& param) : m_param(param), m_currentHP(param.m_maxHP) {}


	/** ダメージ処理 */
	void TakeDamage(float amount);


	/** 回復処理 */
	void Heal(float amount);


	/** 現在のHPを取得 */
	float GetCurrentHP() const { return m_currentHP; }


	/** 最大HPを取得 */
	float GetMaxHP() const { return m_param.m_maxHP; }


	/** 死亡しているかどうかを取得 */
	bool IsDead() const { return m_isDead; }


	/** 死亡時、呼び出す関数 */
	std::function<void()> onDead; 


private:
	bool Start() override { return true; }


	void Update() override;


private:
	const HealthParameter& m_param;
	float m_currentHP;
	bool m_isDead = false;


};

