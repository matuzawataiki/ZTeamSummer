#pragma once
class ViewModelComponent;
class Soldier : public GameObject
{
public:
	Soldier();
	~Soldier();

private:
	ViewModelComponent* m_viewModelComponent;

public:
	bool Start() override;
	void Update() override;
	void Render() override;

private:
	void InitCollider();
	void InitState();
};

