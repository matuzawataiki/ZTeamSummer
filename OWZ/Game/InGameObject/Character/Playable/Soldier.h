#pragma once
class ViewModelComponent;
class Soldier : public GameObject
{
public:
	Soldier();
	~Soldier();

private:
	std::shared_ptr<ViewModelComponent> m_viewModelComponent;

public:
	bool Start() override;
	void Update() override;
	void Render() override;
};

