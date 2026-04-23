#pragma once
class HealingArea : public GameObject
{
private:
	float m_heelHeight = 0;

public: 

	void Init(float areaSize, float heelHeight);

	void HitArea(GameObject* HitObject);
};

