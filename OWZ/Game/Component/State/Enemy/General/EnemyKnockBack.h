#pragma once
#include "Component/State/Enemy/EnemyState.h"


class EnemyKnockBackState : public EnemyState
{
public:
	EnemyKnockBackState() = default;
	~EnemyKnockBackState() override = default;


	void Enter() override;
	void Update() override;
	void Exit() override;


};