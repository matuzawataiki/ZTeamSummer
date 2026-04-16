#pragma once

class TransformComponent;
class ModelComponent;

class ActivatableObject : public GameObject
{
public:
    ActivatableObject();
    ~ActivatableObject();

private:
    std::shared_ptr<TransformComponent> m_transform;
    std::shared_ptr<ModelComponent> m_model;

    bool m_isActivated;                     // 起動完了したかどうかのフラグ
    float m_interactTimer;                  // 長押ししている時間
    const float MAX_INTERACT_TIME = 3.0f;   // 起動に必要な時間

public:
    void Update() override;
    void Render() override;

    void InitParam(const char* modelPath, const Vector3& position);

    // 起動を確認するための関数
    bool IsActivated() const { return m_isActivated; }
};