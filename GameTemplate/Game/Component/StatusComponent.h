#pragma once


class StatusComponent
{
	StatusComponent() {};
	~StatusComponent() {};


private:
	int m_currentHP = 0;
	int m_maxHP = 0;
	int m_attack = 0;


private:
	/**
	 * @brief 更新処理
	 */
	void Update();


public:
	/**
	 * @brief ステータスの設定
	 * @param maxhp , attack
	 */
	void Initialize(int maxhp, int attack);


	/**
	 * @brief 被ダメージの計算
	 * @param damage
	 */
	void ApplyDamage(int damage);
};

