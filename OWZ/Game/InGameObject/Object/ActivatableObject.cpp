#include "stdafx.h"
#include "ActivatableObject.h"

ActivatableObject::ActivatableObject()
{
    m_isActivated = false;
    m_interactTimer = 0.0f;

    AddComponent<TransformComponent>();
    AddComponent<ModelComponent>();

    m_transform = GetComponent<TransformComponent>();
    m_model = GetComponent<ModelComponent>();
}

ActivatableObject::~ActivatableObject()
{
}

void ActivatableObject::InitParam(const char* modelPath, const Vector3& position)
{
    if (m_model) {
        m_model->SetModel(modelPath, false);
        m_model->SetDrawFlag(true);
        m_model->SetPosition(position);
    }
    if (m_transform) {
        m_transform->SetPosition(position);
    }
}

void ActivatableObject::Update()
{
    // すでに起動済みなら何もしない
    if (m_isActivated) return;

    if (g_pad[0]->IsPress(enButtonX)) {

        m_interactTimer += 1.0f / 60.0f;

        // 3秒以上長押ししたら起動完了
        if (m_interactTimer >= MAX_INTERACT_TIME) {
            m_isActivated = true;
            OutputDebugStringA("=== 端末が起動完了しました！ ===\n");
        }
    }
    else {
        m_interactTimer = 0.0f;
    }
}

void ActivatableObject::Render()
{
    if (m_model) {
        m_model->Draw();
    }
}