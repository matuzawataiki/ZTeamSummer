#pragma once

class ModelComponent;
class StageObject : public GameObject
{
private:
	ModelComponent* m_model = nullptr;

public:
	bool Start() override;
};