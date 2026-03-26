#pragma once
#include "MissionBase.h"

class ActivatableObject;

class ActivationMission : public MissionBase
{
public:
    ActivationMission();
    ~ActivationMission();

private:
    std::vector<ActivatableObject*> m_targets;

public:
    void Update() override;

    // 端末を登録してもらう関数
    void AddTarget(ActivatableObject* target);
};