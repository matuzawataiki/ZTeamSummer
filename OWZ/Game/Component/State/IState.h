#pragma once
class IState
{
public:
	virtual ~IState() = default;
public:
	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Exit() = 0;
};

