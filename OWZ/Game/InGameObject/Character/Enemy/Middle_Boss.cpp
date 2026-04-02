#include "stdafx.h"
#include "Middle_Boss.h"

bool Middle_Boss::Start()
{
	auto* params = ParameterManager::GetInstance();
	InitComponents(params, static_cast<int>(CharacterIndex::Middle_Boss), true);


	return true;
}

void Middle_Boss::Update()
{
	EnemyBase::Update();
}

void Middle_Boss::Draw(RenderContext& rc)
{

}

void Middle_Boss::OnUpdate()
{
	// ここにMiddle_Bossの固有の更新処理を追加する
}