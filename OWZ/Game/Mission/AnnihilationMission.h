#pragma once
#include "MissionBase.h"

class DummyEnemy; 

class AnnihilationMission : public MissionBase
{
public:
    AnnihilationMission();
    ~AnnihilationMission();

private:
    std::vector<DummyEnemy*> m_targets;

public:
    void Update() override;
    void AddTarget(DummyEnemy* target);
};