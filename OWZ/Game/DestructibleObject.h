#pragma once

class TransformComponent;
class ModelComponent;

class DestructibleObject : public GameObject
{
public:
    DestructibleObject();
    ~DestructibleObject();

private:
    std::shared_ptr<TransformComponent> m_transform;
    std::shared_ptr<ModelComponent> m_model;

    bool m_isDestroyed;

    std::string m_brokenModelPath;

    void PlayDestroyEffect();

public:
    void Update() override;
    void Render() override;

    // 座標だけでなくモデルのパスも外から受け取るようにする関数
    void InitParam(const char* intactModelPath, const char* brokenModelPath, const Vector3& position);

    // ダメージ処理関数
    void TakeDamage();

    // 壊れているかどうかを外部に教える関数
    bool IsDestroyed() const { return m_isDestroyed; }
};