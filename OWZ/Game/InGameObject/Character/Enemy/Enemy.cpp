#include "stdafx.h"
#include "Enemy.h"
#include "Component/State/Enemy/EnemyStateController.h"
#include "Component/State/Enemy/General/EnemyIdle.h"


Enemy::Enemy() = default;


void Enemy::Initilize(EnemyType type)
{
	m_enemyType = type;


	auto controller = GetComponent<EnemyStateController>();
	if (!controller)
	{
		return;
	}

	m_stateController = controller;


	/** 種類ごとの初期設定をコントローラーに移譲 */
	controller->SetupEnemy(type);

	/** TODO::全エネミー共通の初期ステートはIdle
	  * SetupEnemy内でStateMacniheにInitializeStateを呼ぶ。
	  */
}



void Enemy::Update()
{
	if (auto ctrl = m_stateController.lock())
	{
		ctrl->Update();
	}
}

void Enemy::TakeDamage(float damage)
{
	m_hp -= damage;
	if (m_hp < 0.0f) 
	{
		m_hp = 0.0f;
	}
}
