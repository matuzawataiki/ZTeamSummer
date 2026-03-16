#pragma once
#include "Util/Json/Json.h"


class EnemyStatusComponent : public Component
{
private:
	EnemyStatusComponent();
	~EnemyStatusComponent();


private:
	float m_currentHP = 0.0f;
	float m_maxHP = 0.0f;
	float m_speed = 0.0f;


public:
	/**
	  * 更新処理
	  */
	void Update() override {};


	/**
	  * Jsonファイルからパラメータを読み込む 
	  */
	void LoadFromJson(const std::string& filepath);


	/**
	  * ダメージを受ける処理
	  */
	void TakeDamage(int damageAmount);


public:
	float GetCurrentHP() const { return m_currentHP; }
	float GetMaxHP() const { return m_maxHP; }
	float GetSpeed() const { return m_speed; }
};