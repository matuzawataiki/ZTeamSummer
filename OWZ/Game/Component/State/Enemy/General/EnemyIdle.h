#pragma once
#include "Component/State/Enemy/EnemyState.h"


class EnemyIdleState : public EnemyState
{
public:
	explicit EnemyIdleState(EnemyStateController& controller) : EnemyState(controller) {}
	~EnemyIdleState() override = default;


	void Enter() override;
	void Update() override;
	void Exit() override;


private:
	void UpdateWalk();
	void UpdateFly();
	void UpdateMiddle();
	void UpdateBoss();
};
