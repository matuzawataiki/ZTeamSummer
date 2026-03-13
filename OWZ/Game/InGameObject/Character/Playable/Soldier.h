#pragma once
class ViewModelComponent;
class Soldier : public GameObject
{
public:
	Soldier();
	~Soldier();

private:
	std::shared_ptr<ViewModelComponent> m_model;

public:
	void Render()override;
};

