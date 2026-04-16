#include "stdafx.h"
#include "GameScene.h"
#include "Scene/SceneManager.h"
#include "InGameObject/Character/Playable/Soldier.h"
#include "InGameObject/Object/DestructibleObject.h"
#include "Mission/DestructionMission.h"
#include "Mission/MissionManager.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Initialize()
{
	m_test = new Soldier;
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

	m_missionManager = std::make_unique<MissionManager>();

	auto destructionMission = std::make_shared<DestructionMission>();

	destructionMission->AddTarget(m_tower);
	destructionMission->AddTarget(m_tower2);

	m_missionManager->AddMission(destructionMission);
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

	// ミッションの更新
	if (m_missionManager) {
		m_missionManager->Update();
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
}

void GameScene::Finalize()
{
	delete m_test;
	m_test = nullptr;

	delete m_tower;
	m_tower = nullptr;

	delete m_tower2;
	m_tower2 = nullptr;

	m_missionManager.reset();
}
