#include "stdafx.h"
#include "GameScene.h"
#include "Scene/SceneManager.h"
#include "InGameObject/Character/Playable/Soldier.h"
#include "DestructibleObject.h"

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

	// 破壊ミッションの生成と登録
	//DestructionMission* mission = new DestructionMission();
	//mission->AddTarget(m_tower);  // 1つ目を登録
	//mission->AddTarget(m_tower2); // 2つ目を登録

	// 管理を任せる
	//m_currentMission = mission;
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

	delete m_currentMission;
	m_currentMission = nullptr;
}
