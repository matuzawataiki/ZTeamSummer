#include "stdafx.h"
#include "ActivationMission.h"
#include "InGameObject/Object/ActivatableObject.h"

ActivationMission::ActivationMission() : MissionBase()
{
}

ActivationMission::~ActivationMission()
{
}

void ActivationMission::AddTarget(std::shared_ptr<ActivatableObject> target)
{
    if (target) {
        m_targets.push_back(target);
    }
}

void ActivationMission::Update()
{
    if (m_isCleared) return;
    if (m_targets.empty()) return;

    // まだ起動していない端末の数を数える
    int remainingCount = 0;

    for (auto it = m_targets.begin();it!= m_targets.end();) {
        // weak_ptrからshared_ptrにロックする
        if (auto target = it->lock()) {

            // 実体が存在する場合のみ起動しているかチェック
            if (!target->IsActivated()) {
                remainingCount++;
            }
            ++it; // 次の要素へ

        }
        else {
            // もしGameScene側で既にオブジェクトが消されていたら、リストから除外する
            it = m_targets.erase(it);
        }
    }

    // すべて起動していたら
    if (remainingCount == 0 && !m_targets.empty()) {
        m_isCleared = true;
        OutputDebugStringA("===== オブジェクト起動ミッション クリア！！！ =====\n");
    }
}