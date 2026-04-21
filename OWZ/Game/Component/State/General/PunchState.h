#pragma once
#include "Component/State/IState.h"

class Punch;
class PunchState : public IState
{
private:
	Punch* m_wepon = nullptr;

public:
	void SetWepon(Punch* wepon) { m_wepon = wepon; }

	void Enter() override;
	void Update() override;
	void Exit() override;
};

