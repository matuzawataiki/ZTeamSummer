#include "stdafx.h"
#include "ActivationMission.h"
#include "InGameObject/Object/ActivatableObject.h"

ActivationMission::ActivationMission()
{
}

ActivationMission::~ActivationMission()
{
}

void ActivationMission::AddTarget(ActivatableObject* target)
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
    for (auto target : m_targets) {
        if (!target->IsActivated()) {
            remainingCount++;
        }
    }

    // すべて起動していたら
    if (remainingCount == 0) {
        m_isCleared = true;
        OutputDebugStringA("===== オブジェクト起動ミッション クリア！！！ =====\n");
    }
}