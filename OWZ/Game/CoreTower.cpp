#include "stdafx.h"
#include "CoreTower.h"

namespace {
    const char* TOWER_MODEL_PATH = "Assets/modelData/gimmick/breakObj/model/breakObjTower.tkm";
}

CoreTower::CoreTower()
{
}

CoreTower::~CoreTower()
{
}

void CoreTower::Init(const Vector3& position)
{
    m_transform = std::make_unique<TransformComponent>();
    m_transform->SetPosition(position);

    m_model = std::make_unique<ModelComponent>();

    // アニメーションなしでモデルをセットして描画を有効にする
    m_model->SetModel(TOWER_MODEL_PATH, false);
    m_model->SetDrawFlag(true);

    m_model->SetPosition(position);
}

void CoreTower::Draw()
{
    if (m_model) {
        m_model->Draw();
    }
}