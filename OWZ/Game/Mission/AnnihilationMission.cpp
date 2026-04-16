#include "stdafx.h"
#include "AnnihilationMission.h"
#include "DummyEnemy.h" 

AnnihilationMission::AnnihilationMission()
{
}

AnnihilationMission::~AnnihilationMission()
{
}

void AnnihilationMission::AddTarget(DummyEnemy* target)
{
    if (target) {
        m_targets.push_back(target);
    }
}

void AnnihilationMission::Update()
{
    if (m_isCleared) return;
    if (m_targets.empty()) return;

    int remainingCount = 0;
    for (auto target : m_targets) {
        if (!target->IsDead()) {
            remainingCount++;
        }
    }

    if (remainingCount == 0) {
        m_isCleared = true;
        OutputDebugStringA("===== 敵殲滅ミッション クリア！！！ =====\n");
    }
}