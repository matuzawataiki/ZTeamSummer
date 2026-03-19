#pragma once

class TransformComponent;
class ModelComponent;

class CoreTower : public Noncopyable
{
public:
    CoreTower();
    ~CoreTower();

private:
    std::unique_ptr<TransformComponent> m_transform;
    std::unique_ptr<ModelComponent> m_model;

public:
    void Init(const Vector3& position);
    void Draw();
};