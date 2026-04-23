#pragma once

class MissionBase;

class MissionManager
{
public:
    MissionManager();
    ~MissionManager();

private:
    // 登録されたミッションを入れておくリスト
    std::vector<std::shared_ptr<MissionBase>> m_missions;

    // 今、何番目のミッションを実行しているか
    int m_currentMissionIndex;

public:
    // ミッションを追加する関数
    void AddMission(std::shared_ptr<MissionBase> mission);

    void Update();

    // 全てのミッションをクリアしたかを確認する関数
    bool IsAllMissionsCleared() const;
};