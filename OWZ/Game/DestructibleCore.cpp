#include "stdafx.h"
#include "DestructibleCore.h"

namespace {
    const char* CORE_MODEL_PATH = "Assets/modelData/gimmick/breakObj/model/breakObjTower.tkm";
    const char* CORE_ANIM_IDLE = "Assets/modelData/gimmick/breakObj/animation/breakObjCore.tka";
}

DestructibleCore::DestructibleCore()
{
    m_isDestroyed = false;
}

DestructibleCore::~DestructibleCore()
{
}

void DestructibleCore::Init(const Vector3& position)
{
    m_transform = std::make_unique<TransformComponent>();
    
    Vector3 corePos = position;
    corePos.y += 50.0f; 

    m_transform->SetPosition(corePos);


    //m_transform->SetPosition(position);

    m_model = std::make_unique<ModelComponent>();

	//m_model->AddAnimation(CORE_ANIM_IDLE, true);    // 待機アニメーションはループする
	m_model->SetModel(CORE_MODEL_PATH, false);        // アニメーションありでモデルをセット
	m_model->SetDrawFlag(true);                       // 描画フラグを有効にする
	m_model->SetPosition(corePos);                   // モデルの位置を設定
}

void DestructibleCore::Update()
{
    if (m_isDestroyed) {
        return;
    }

    if (g_pad[0]->IsTrigger(enButtonX)) {
        DebugTakeDamage();
    }
}

void DestructibleCore::Draw()
{
    if (!m_isDestroyed && m_model) {
        m_model->Draw();
    }
}

void DestructibleCore::PlayDestroyEffect()
{      
    // 直接メンバ変数を操作する
    if (m_model) {
		m_model->SetDrawFlag(false);    //破壊されたらモデルを非表示にする
    }
}

void DestructibleCore::DebugTakeDamage()
{
    m_isDestroyed = true;
    PlayDestroyEffect();
}