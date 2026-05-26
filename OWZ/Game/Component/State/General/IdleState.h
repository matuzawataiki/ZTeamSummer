#pragma once
#include "Component/State/IState.h"

class IdleState : public IState
{
private:
	GameObject* m_owner = nullptr;

public:
	void SetOwner(GameObject* gameObject) {
		m_owner = gameObject;
	}

	void Enter();
	void Update();
	void Exit();
};

