#pragma once
#include "Component/State/Enemy/EnemyState.h"


class EnemyStunState : public EnemyState
{
public:
	EnemyStunState() = default;
	~EnemyStunState() override = default;


	void Enter() override;
	void Update() override;
	void Exit() override;


};
