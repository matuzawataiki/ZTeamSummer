#include "stdafx.h"
#include "MissionBase.h"

MissionBase::MissionBase()
{
    // 生成時は必ず未クリア状態にしておく
    m_isCleared = false;
}

MissionBase::~MissionBase()
{
}

void MissionBase::Update()
{
}