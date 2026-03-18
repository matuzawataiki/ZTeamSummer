#include "stdafx.h"
#include "InteractComponent.h"

InteractComponent::InteractComponent()
{
}

InteractComponent::~InteractComponent()
{
}

void InteractComponent::Update()
{
    // すでに起動完了している場合は、これ以上処理しない
    if (m_currentState == enActivated) {
        return;
    }

    // プレイヤーがアクセス可能な距離にいるかチェック
    if (CheckPlayerDistance()) {
        if (g_pad[0]->IsPress(enButtonF)) {
            StartInteract();
        }
        else {
            // ボタンを離したらキャンセル
            CancelInteract();
        }
    }
    else {
        // 範囲外に出たらキャンセル
        CancelInteract();
    }

    // インタラクト中
    if (m_currentState == enInteracting) {
        // 時間を進める
        m_interactProgressTime += g_gameTime->GetFrameDeltaTime();

        // 規定時間に達したか？
        if (m_interactProgressTime >= REQUIRED_INTERACT_TIME) {
            m_currentState = enActivated;
        }
    }
}

// インタラクト開始
void InteractComponent::StartInteract()
{
    // 待機中のみ、インタラクト状態に移行
    if (m_currentState == enIdle) {
        m_currentState = enInteracting;
    }
}

// インタラクト中断
void InteractComponent::CancelInteract()
{
    // インタラクト中にボタンを離すと進行度をリセットする
    if (m_currentState == enInteracting) {
        m_currentState = enIdle;
        m_interactProgressTime = 0.0f;
    }
}

// 起動完了状態の取得
bool InteractComponent::GetIsActivated() const
{
    return m_currentState == enActivated;
}

bool InteractComponent::CheckPlayerDistance()
{
    //　仮の実装
    //　動作確認のために常にtrueを返す
    return true;
}