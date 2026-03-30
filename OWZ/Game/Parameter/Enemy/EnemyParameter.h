#pragma once
#include "Parameter/IMasterParameter.h"
#include <string>
#include <vector>


/** 攻撃パターン */
struct AttackPattern
{
	std::string patternName;				//攻撃パターンの名前
	float damage = 0.0f;			//ダメージ
	float attackRange = 0.0f;		//攻撃範囲
	float coolTime = 0.0f;			//クールタイム
	float trrigerHPRatio = 0.0f;	//この攻撃パターンが発動する体力の割合（例: 0.5は体力が50%以下のときに発動）

};


/** Jsonから読み込むエネミーパラメータ */
struct EnemyParameter : public IMasterParameter
{
	appParameter(EnemyParameter)


public:
	std::string enemyType = "";					//エネミーの名前
	float hp = 0.0f;							//体力
	float moveSpeed = 0.0f;						//移動速度
	float detectionRange = 0.0f;				//索敵範囲
	float attackRange = 0.0f;					//攻撃範囲
	float attackDamage = 0.0f;					//攻撃力
	float attackCoolTime = 0.0f;				//攻撃のクールタイム
	float altitube = 0.0f;						//高度(Fly専用 Fly以外は0でいい)


	std::vector<AttackPattern> attackPatterns;	//攻撃パターン
};