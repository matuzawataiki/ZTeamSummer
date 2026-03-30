#pragma once
#include "Component/State/IState.h"
#include "Component/State/Enemy/EnemyStateController.h"


/** EnemyStateの基底クラス */
class EnemyState : public IState
{
public:
	explicit EnemyState(EnemyStateController& controller) : m_controller(controller) {}
	~EnemyState() override = default;


	void Enter() override {};
	void Update() override {};		//視野チェックでステート移行
	void Exit() override {};


protected:
	EnemyStateController& m_controller;	//状態を管理するコントローラーへの参照
};