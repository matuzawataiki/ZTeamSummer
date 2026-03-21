#include "stdafx.h"
#include "DestructibleTower.h"

namespace {
    // 破壊前のモデル
    const char* TOWER_MODEL_INTACT = "Assets/modelData/gimmick/breakObj/model/ObjTower.tkm";
    // 破壊後のモデル
    const char* TOWER_MODEL_BROKEN = "Assets/modelData/gimmick/breakObj/model/breakObjTower.tkm";
}

DestructibleTower::DestructibleTower()
{
    m_isDestroyed = false;

    AddComponent<TransformComponent>();
    AddComponent<ModelComponent>();

    m_transform = GetComponent<TransformComponent>();
    m_model = GetComponent<ModelComponent>();

    // 初期状態（破壊前）のモデルをセット
    m_model->SetModel(TOWER_MODEL_INTACT, false);
    m_model->SetDrawFlag(true);
}

DestructibleTower::~DestructibleTower()
{
}

void DestructibleTower::PlayDestroyEffect()
{
    // モデルを破壊後のものに切り替える
    if (m_model) {
        m_model->SetModel(TOWER_MODEL_BROKEN, false);
    }
}

void DestructibleTower::Update()
{
    // すでに破壊されていたら何もしない
    if (m_isDestroyed) {
        return;
    }

    // デバッグ用：Xボタンで破壊テスト
    if (g_pad[0]->IsTrigger(enButtonX)) {
        TakeDamage();
    }
}

void DestructibleTower::Render()
{
    if (m_model) {
        m_model->Draw();
    }
}

void DestructibleTower::SetPosition(const Vector3& position)
{
    // TransformとModelの両方に座標を伝える
    if (m_transform) {
        m_transform->SetPosition(position);
    }
    if (m_model) {
        m_model->SetPosition(position);
    }
}

void DestructibleTower::TakeDamage()
{
    if (m_isDestroyed) return;

    m_isDestroyed = true;
    PlayDestroyEffect();
}