#pragma once
#include "MissionBase.h"

class ActivatableObject;

class ActivationMission : public MissionBase
{
public:
    ActivationMission();
    ~ActivationMission();

private:
    std::vector<std::weak_ptr<ActivatableObject>> m_targets;

public:
    void Update() override;

    // 端末を登録してもらう関数
	void AddTarget(std::shared_ptr<ActivatableObject>target);
};