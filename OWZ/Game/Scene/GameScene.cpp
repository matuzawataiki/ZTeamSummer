#include "stdafx.h"
#include "GameScene.h"
#include "Scene/SceneManager.h"
#include "InGameObject/Character/Playable/Soldier.h"
#include "DestructibleTower.h"


GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Initialize()
{
	m_test = new Soldier;
	m_tower = new DestructibleTower;
	m_tower->SetPosition(Vector3(50.0f, 0.0f, 0.0f));
}

void GameScene::Update(SceneManager& manager)
{
	m_test->StartWrapper();
	m_test->UpdateWrapper();

	if (m_tower) {
		m_tower->StartWrapper();
		m_tower->UpdateWrapper();
	}
}

void GameScene::Draw()
{
	m_test->Render();

	if (m_tower) {
		m_tower->Render();
	}
}

void GameScene::Finalize()
{
	delete m_test;
	m_test = nullptr;

	delete m_tower;
	m_tower = nullptr;
}
