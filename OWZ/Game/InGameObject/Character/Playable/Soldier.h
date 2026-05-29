#pragma once
class ViewModelComponent;
class Soldier : public GameObject
{
public:
	Soldier();
	~Soldier();

private:
	ViewModelComponent* m_viewModelComponent;
	float m_yaw = 0.0f;
	float m_pitch = 0.0f;
public:
	bool Start() override;
	void Update() override;
	void Render() override;

private:
	void InitModel();
	void InitSkill();
	void InitCollider();
	void InitState();
};

