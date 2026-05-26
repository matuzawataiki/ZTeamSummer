#pragma once
#include "Component/State/IState.h"

class Punch;
class PunchState : public IState
{
private:
	Punch* m_weapon = nullptr;

public:
	void SetWepon(Punch* wepon) { m_weapon = wepon; }

	void Enter() override;
	void Update() override;
	void Exit() override;
};

