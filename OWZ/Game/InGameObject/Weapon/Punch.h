#pragma once
class Punch : public GameObject
{
private:
	Vector3 m_offset = Vector3(0.0f, 150.0f, 50.0f);
	bool m_fierFlag = false;
	bool m_activeFlag = false;

public:
	bool Start()override;
	void Update() override;

	void Fire();

	void Hit(const HitResult& hitResult);
};

