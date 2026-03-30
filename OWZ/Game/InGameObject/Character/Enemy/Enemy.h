#pragma once
#include "InGameObject/Character/Enemy/EnemyType.h"
#include "Component/State/Enemy/EnemyStateController.h"


class Enemy :public GameObject
{
	appClass(Enemy);


public:
	Enemy();
	~Enemy() = default;


	/** 初期化(種類を指定してステートマシンをセットアップ) */
	void Initilize(EnemyType type) ;


	float GetHP() const { return m_hp; }
	float GetMaxHP() const { return m_maxHP; }
	float GetMoveSpeed() const { return m_moveSpeed; }


	/** ダメージを受ける */
	void TakeDamage(float damage);


	/** 敵の種類を返す */
	EnemyType GetEnemyType() const { return m_enemyType; }


private:
	void Update() override;


private:
	EnemyType m_enemyType = EnemyType::Walk;
	std::weak_ptr <EnemyStateController> m_stateController;


private:
	float m_hp = 0.0f; // 体力
	float m_maxHP = 0.0f; // 最大体力
	float m_moveSpeed = 0.0f; // 移動速度

};