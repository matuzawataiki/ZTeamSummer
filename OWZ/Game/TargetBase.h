#pragma once

class TargetBase : public GameObject
{
public:
	TargetBase() = default;
	~TargetBase() = default;

private:
	bool m_isInit = false;
	int m_point = 0.0f;
	ModelComponent* m_model = nullptr;

public:
	void Init(const char* mfilePath, int point, Vector3 position, Quaternion rotation);

private:
	void Hit();
};

