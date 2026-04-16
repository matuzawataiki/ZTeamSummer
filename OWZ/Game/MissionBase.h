#pragma once

// ミッションの親となるベースクラス
class MissionBase : public GameObject
{
public:
    MissionBase();
    virtual ~MissionBase();

protected:
    bool m_isCleared;

public:
    virtual void Update() override;

    // クリア状況を確認するための関数
    bool IsCleared() const { return m_isCleared; }
};