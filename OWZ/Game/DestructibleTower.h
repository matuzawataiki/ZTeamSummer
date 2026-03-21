#pragma once

class TransformComponent;
class ModelComponent;

class DestructibleTower : public GameObject
{
public:
    DestructibleTower();
    ~DestructibleTower();

private:
    std::shared_ptr<TransformComponent> m_transform;
    std::shared_ptr<ModelComponent> m_model;

    bool m_isDestroyed;

    void PlayDestroyEffect();

public:
    void Update() override;
    void Render() override;

    // 外部から座標を設定する関数
    void SetPosition(const Vector3& position);

    // ダメージ処理
    void TakeDamage();
};