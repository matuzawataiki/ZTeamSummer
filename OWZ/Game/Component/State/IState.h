#pragma once
class IState
{
public:
	virtual ~IState() = default;
public:
	virtual void Enter();
	virtual void Update();
	virtual void Exit();
};

