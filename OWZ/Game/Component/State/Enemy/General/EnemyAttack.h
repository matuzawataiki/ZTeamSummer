#pragma once
#include "Component/State/Enemy/EnemyState.h"


class EnemyAttack : public EnemyState
{
public:
	EnemyAttack() = default;
	~EnemyAttack() override = default;


	void Enter() override;
	void Update() override;
	void Exit() override;


};

