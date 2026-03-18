#pragma once
class IState
{
public:
	virtual ~IState() = default;
public:
	int m_statePriority = 100;

public:
	virtual void Enter();
	virtual void Update();
	virtual void Exit();

};

