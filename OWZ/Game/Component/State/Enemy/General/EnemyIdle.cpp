#include "stdafx.h"
#include "EnemyIdle.h"


void EnemyIdleState::Enter()
{
}

void EnemyIdleState::Update()
{
	switch (m_controller.GetEnemyType())
	{
		case EnemyType::Walk:UpdateWalk(); break;
		case EnemyType::Fly:UpdateFly(); break;
		case EnemyType::Middle:UpdateMiddle(); break;
		case EnemyType::Boss:UpdateBoss(); break;
	}
}

void EnemyIdleState::Exit()
{
}

void EnemyIdleState::UpdateWalk()
{
	/** この中に各エネミーのUpdateの処理を書く */
}

void EnemyIdleState::UpdateFly()
{
}

void EnemyIdleState::UpdateMiddle()
{
}

void EnemyIdleState::UpdateBoss()
{
}


