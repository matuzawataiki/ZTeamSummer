#include "stdafx.h"
#include "EnemyStateController.h"
#include "Parameter/Enemy/EnemyParameter.h"
#include "Parameter/ParameterManager.h"
#include "Component/State/Enemy/General/EnemyIdle.h"
#include "Component/State/StateMachineComponent.h"


EnemyStateController::EnemyStateController() = default;

EnemyStateController::~EnemyStateController() = default;

void EnemyStateController::SetupEnemy(EnemyType type)
{
	m_enemyType = type;


	// 敵の種類に応じた初期設定をここで行う
	m_parameter = GetEnemyParameter(type);


	auto sm = GetComponent<StateMachineComponent>();
	if (sm)
	{
		sm->InitializeState(std::make_unique<EnemyIdleState>(*this));
	}
}


void EnemyStateController::Update()
{
	// 更新処理
}


bool EnemyStateController::CanSeePlayer() const
{
	// プレイヤーが見つけたかどうか
	return false;
}

std::string EnemyStateController::EnemyTypeToString(EnemyType type) const
{
	switch (type)
	{
	case EnemyType::Walk: return "Walk";
	case EnemyType::Fly: return "Fly";
	case EnemyType::Middle: return "Middle";
	case EnemyType::Boss: return "Boss";
	}
	return "";
}

const EnemyParameter* EnemyStateController::GetEnemyParameter(EnemyType type) const
{
	std::string typeName = EnemyTypeToString(type);


	const EnemyParameter* result = nullptr;
	ParameterManager::GetInstance()->ForEach<EnemyParameter>([&](const EnemyParameter& p)
		{
			if (p.enemyType == typeName)
			{
				result = &p;
			}
			
		});

	return result;
}
