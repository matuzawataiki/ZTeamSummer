#pragma once
class GoalObject : public GameObject
{
public:
	GoalObject() = default;
	~GoalObject() = default;
	void Init();
	void Hit();

	bool m_isHit;
};

