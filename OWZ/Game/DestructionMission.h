#pragma once
#include "MissionBase.h"

class DestructibleObject;

class DestructionMission : public MissionBase
{
public:
    DestructionMission();
    ~DestructionMission();

private:
    // 壊すターゲットを覚えておくリスト
    std::vector<DestructibleObject*> m_targets;

public:
    void Update() override;

    // GameSceneからターゲットを登録してもらう関数
    void AddTarget(DestructibleObject* target);
};