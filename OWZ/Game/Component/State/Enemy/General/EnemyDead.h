#pragma once
#include "Component/State/Enemy/EnemyState.h"


class EnemyDeadState : public EnemyState
{
public:
	EnemyDeadState() = default;
	~EnemyDeadState() override = default;


	void Enter() override;
	void Update() override;
	void Exit() override;


};