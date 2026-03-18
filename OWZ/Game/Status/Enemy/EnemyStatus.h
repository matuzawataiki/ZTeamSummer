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


public:
	/** 更新処理 */
	void Update() override {};


	/** Jsonファイルからパラメータを読み込む */
	void LoadStatus(const char* path, const std::function<void(const nlohmann::json& j)>& func);


};