#pragma once
#include "Component/State/IAIState.h"

class IdleAIState : public IAIState
{
public:
	IdleAIState() { 
		m_statePriority = 1; 
		Active();
	}

public:
	void Enter() override {
		int i = 0;
	}

	void Update() override{}
	void Exit() override {}

};

