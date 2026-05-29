#pragma once

class ModelComponent;
class StageObject : public GameObject
{
private:
	ModelComponent* m_model = nullptr;

public:
	bool Start() override;

	void Init(Vector3 position,Quaternion rotetion);

	void Render() override;
};