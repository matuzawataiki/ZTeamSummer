#include "stdafx.h"
#include "DestructionMission.h"
#include "InGameObject/Object/DestructibleObject.h"

DestructionMission::DestructionMission()
{
}

DestructionMission::~DestructionMission()
{
}

void DestructionMission::AddTarget(DestructibleObject* target)
{
    if (target) {
        m_targets.push_back(target);
    }
}

void DestructionMission::Update()
{
    // すでにクリア済みならチェックしない
    if (m_isCleared) return;

    // ターゲットが1つも登録されていなければ何もしない
    if (m_targets.empty()) return;

    // 残りの目標の数を数える
    int remainingCount = 0;
    for (auto target : m_targets) {
        if (!target->IsDestroyed()) {
            remainingCount++; // まだ壊れていないものをカウント
        }
    }

    // すべて壊れていたらクリア判定にする
    if (remainingCount == 0) {
        m_isCleared = true;
        
        // デバック用
        OutputDebugStringA("===== オブジェクト破壊ミッション クリア！！！ =====\n");
    }
}