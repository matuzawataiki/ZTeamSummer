#include "stdafx.h"
#include "GameScene.h"
#include "Scene/SceneManager.h"
#include "InGameObject/Character/Playable/Soldier.h"


GameScene::GameScene()
{
	m_test = new Soldier;
}

GameScene::~GameScene()
{
}

void GameScene::Initialize()
{
}

void GameScene::Update(SceneManager& manager)
{
	m_test->StartWrapper();
	m_test->UpdateWrapper();
}

void GameScene::Draw()
{
	m_test->Render();
}

void GameScene::Finalize()
{
}
