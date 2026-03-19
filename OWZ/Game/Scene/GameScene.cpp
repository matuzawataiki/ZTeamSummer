#include "stdafx.h"
#include "GameScene.h"
#include "Scene/SceneManager.h"
#include "InGameObject/Character/Playable/Soldier.h"
#include "DestructibleCore.h"
#include "CoreTower.h"


GameScene::GameScene()
{
	m_test = new Soldier;
}

GameScene::~GameScene()
{
}

void GameScene::Initialize()
{
	Vector3 spawnPositions[3] = {
		Vector3(0.0f, 0.0f, 100.0f),
		Vector3(100.0f, 0.0f, 0.0f),
		Vector3(-100.0f, 0.0f, 0.0f)
	};

	for (int i = 0; i < 3; ++i) {
		auto core = std::make_unique<DestructibleCore>();
		core->Init(spawnPositions[i]);
		m_cores.push_back(std::move(core));

		auto tower = std::make_unique<CoreTower>();
		tower->Init(spawnPositions[i]);
		m_towers.push_back(std::move(tower));
	}
}

void GameScene::Update(SceneManager& manager)
{
	m_test->StartWrapper();
	m_test->UpdateWrapper();

	for (auto& core : m_cores) {
		core->Update();
	}
}

void GameScene::Draw()
{
	m_test->Render();

	for (auto& tower : m_towers) {
		tower->Draw();
	}
	for (auto& core : m_cores) {
		core->Draw();
	}
}

void GameScene::Finalize()
{
}
