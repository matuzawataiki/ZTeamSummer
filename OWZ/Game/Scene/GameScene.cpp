#include "stdafx.h"
#include "GameScene.h"
#include "Scene/SceneManager.h"
#include "Scene/EndScene.h"
#include "InGameObject/Character/Playable/Soldier.h"
#include "TargetManager.h"
#include "ProjectileManager.h"
#include "GoalObject.h"

GameScene::GameScene()
{
	m_player = std::make_unique<Soldier>();
	m_goal = std::make_unique<GoalObject>();
	m_goal->Init();

	ProjectileManager::CreateInstance();

	TargetManager::CreateInstance();
	TargetManager::GetInstance()->Init();

	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	g_camera3D->SetFar(10000000000.0f);

}

GameScene::~GameScene()
{
}

void GameScene::Initialize()
{
}

void GameScene::Update(SceneManager& manager)
{
	m_player->StartWrapper();
	m_player->UpdateWrapper();
	m_player->Render();


	ProjectileManager::GetInstance()->Update();
	TargetManager::GetInstance()->Update();

	if (m_goal->m_isHit) {
		manager.ChangeScene<EndScene>();
	}
}

void GameScene::Finalize()
{
}
