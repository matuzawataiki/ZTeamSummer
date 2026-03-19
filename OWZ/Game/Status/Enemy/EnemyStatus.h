#pragma once
#include "Util/Json/Json.h"
#include "Status/HP/HPData.h"

class EnemyStatus : public Component
{
private:
	EnemyStatus();
	~EnemyStatus();


private:
	HPData m_hpData;	// HPデータ


};