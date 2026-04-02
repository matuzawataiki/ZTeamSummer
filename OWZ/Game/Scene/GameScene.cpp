	#include "stdafx.h"
#include "GameScene.h"
#include "Scene/SceneManager.h"
#include "InGameObject/Character/Playable/Soldier.h"
#include "DestructibleObject.h"
#include "Parameter/ParameterManager.h"
#include "Parameter/General/HealthParameter.h"
#include "Parameter/General/MoveParameter.h"
#include "Parameter/General/AttackParameter.h"
#include "Parameter/General/AIBehaviorParameter.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Initialize()
{
	// パラメーターの読み込み
	LoadParameters();

	m_test = new Soldier;

	m_enemies.push_back(std::make_shared<Walk_Enemy>());
	m_enemies.push_back(std::make_shared<Middle_Boss>());

	for (auto& enemy : m_enemies)
	{
		enemy->Start();

		// プレイヤーのTransformを敵に渡す(まだ渡せていないからコメントアウト)
		//enemy->SetPlayerTransform(m_test->GetTransform());
	}


	m_tower = new DestructibleObject();
	m_tower->InitParam(
		"Assets/modelData/gimmick/breakObj/model/ObjTower.tkm",      // 破壊前
		"Assets/modelData/gimmick/breakObj/model/breakObjTower.tkm", // 破壊後
		Vector3(0.0f, 0.0f, 0.0f)                                    // 座標
	);

	m_tower2 = new DestructibleObject();
	m_tower2->InitParam(
		"Assets/modelData/gimmick/breakObj/model/ObjTower.tkm",
		"Assets/modelData/gimmick/breakObj/model/breakObjTower.tkm",
		Vector3(150.0f, 0.0f, 0.0f)
	);

	// 破壊ミッションの生成と登録
	//DestructionMission* mission = new DestructionMission();
	//mission->AddTarget(m_tower);  // 1つ目を登録
	//mission->AddTarget(m_tower2); // 2つ目を登録

	// 管理を任せる
	//m_currentMission = mission;
}

void GameScene::LoadParameters()
{
	auto params = ParameterManager::GetInstance();


	params->LoadParameter<HealthParameter>("Assets/Json/Health_Parameter.Json", [](const nlohmann::json& j, HealthParameter& p)
		{
            p.m_maxHP = j.value("maxHP", j.value("maxHp", p.m_maxHP));
			p.m_regenRate = j.value("regenRate", p.m_regenRate);
		});


	params->LoadParameter<MoveParameter>("Assets/Json/Move_Parameter.Json", [](const nlohmann::json& j, MoveParameter& p)
		{
			p.m_moveSpeed = j.value("moveSpeed", p.m_moveSpeed);
			p.m_jumpHeight = j.value("jumpHeight", p.m_jumpHeight);
		});


	params->LoadParameter<AttackParameter>("Assets/Json/Attack_Parameter.Json", [](const nlohmann::json& j, AttackParameter& p)
		{
			p.m_damage = j.value("damage", p.m_damage);
			p.m_range = j.value("range", p.m_range);
			p.m_fireRate = j.value("fireRate", p.m_fireRate);
		});


	params->LoadParameter<AIBehaviorParameter>("Assets/Json/AIBehavior_Parameter.Json", [](const nlohmann::json& j, AIBehaviorParameter& p)
		{
         p.m_ditectionRange = j.value("ditectionRange", j.value("detectionRange", p.m_ditectionRange));
		});
}

void GameScene::Update(SceneManager& manager)
{
	m_test->StartWrapper();
	m_test->UpdateWrapper();

	if (m_tower) {
		m_tower->StartWrapper();
		m_tower->UpdateWrapper();
	}

	if (m_tower2) {
		m_tower2->StartWrapper();
		m_tower2->UpdateWrapper();
	}

	//// ミッションの更新
	//if (m_currentMission) {
	//	m_currentMission->StartWrapper();
	//	m_currentMission->UpdateWrapper();
	//}

	// 敵の更新
	for (auto& enemy : m_enemies)
	{
		// m_hpBar->SetValue(enemy->GetHPRatio()); // HPバーのターゲットを敵に設定(まだHPバーがないからコメントアウト)
	}
}

void GameScene::Draw()
{
	m_test->Render();

	if (m_tower) {
		m_tower->Render();
	}

	if (m_tower2) {
		m_tower2->Render();
	}

	for (auto& enemy : m_enemies)
	{
		enemy->Draw(g_graphicsEngine->GetRenderContext());
	}
}

void GameScene::Finalize()
{
	delete m_test;
	m_test = nullptr;

	delete m_tower;
	m_tower = nullptr;

	delete m_tower2;
	m_tower2 = nullptr;

	delete m_currentMission;
	m_currentMission = nullptr;
}
