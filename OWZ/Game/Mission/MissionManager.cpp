#include "stdafx.h"
#include "MissionManager.h"
#include "MissionBase.h"

MissionManager::MissionManager()
{
    m_currentMissionIndex = 0;
}

MissionManager::~MissionManager()
{
}

void MissionManager::AddMission(std::shared_ptr<MissionBase> mission)
{
    if (mission) {
        m_missions.push_back(mission);
    }
}

void MissionManager::Update()
{
    // 登録されているミッションが無い、または全てクリア済みなら何もしない
    if (m_missions.empty() || m_currentMissionIndex >= m_missions.size()) {
        return;
    }

    auto currentMission = m_missions[m_currentMissionIndex];

    if (currentMission) {
        // ミッションの処理を進める
        currentMission->StartWrapper();
        currentMission->UpdateWrapper();

        // もし今のミッションがクリアされたら
        if (currentMission->IsCleared()) {
            // インデックスを1つ増やして、次のミッションへ移行する
            m_currentMissionIndex++;

            if (m_currentMissionIndex < m_missions.size()) {
                OutputDebugStringA("=== 次のミッションへ移行します！ ===\n");
            }
            else {
                OutputDebugStringA("=== 全ミッションコンプリート！！！ ===\n");
            }
        }
    }
}

bool MissionManager::IsAllMissionsCleared() const
{
    // ミッションが1つ以上登録されていて、かつインデックスが最後まで到達していれば全クリア
    return !m_missions.empty() && m_currentMissionIndex >= m_missions.size();
}