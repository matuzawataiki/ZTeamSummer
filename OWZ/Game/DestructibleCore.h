#pragma once

class TransformComponent;
class ModelComponent;

class DestructibleCore : public Noncopyable
{
public:
    DestructibleCore();
    ~DestructibleCore();

private:
    std::unique_ptr<TransformComponent> m_transform;
    std::unique_ptr<ModelComponent> m_model;

    bool m_isDestroyed;
    void PlayDestroyEffect();   // 破壊エフェクトを再生するための関数

public:
    void Init(const Vector3& position);
    void Update();
    void Draw();

    // デバッグ用のダメージ関数
    void DebugTakeDamage();
};