#pragma once
class IAIState
{
public:
	virtual ~IAIState() = default;

protected:
	int m_statePriority = 100;
	float m_stateTime = 0;

	bool m_lockFlag = false;
	bool m_isActive = false;
	bool m_isIdle = false;

public:
	virtual void Enter(){}
	virtual void Update(){}
	virtual void Exit(){}

	virtual bool ChangeRequest(IAIState* nextState);

	int GetPriority() const { return m_statePriority; }

	void Locking() { m_lockFlag = true; }
	void Unlock() { m_lockFlag = false; }

	void Active() { m_isActive = true; }
	bool IsActive() const { return m_isActive; }

	bool IsIdle() const { return m_isIdle; }


};

