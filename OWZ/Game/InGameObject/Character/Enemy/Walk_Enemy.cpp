#include "stdafx.h"
#include "Walk_Enemy.h"

bool Walk_Enemy::Start()
{
	auto* params = ParameterManager::GetInstance();
	InitComponents(params, static_cast<int>(CharacterIndex::Walk_Enemy), true);


    return true;
}

void Walk_Enemy::Update()
{
	EnemyBase::Update();
}

void Walk_Enemy::Draw(RenderContext& rc)
{
}

void Walk_Enemy::OnUpdate()
{
	// ここにWalk_Enemyの固有の更新処理を追加する
}