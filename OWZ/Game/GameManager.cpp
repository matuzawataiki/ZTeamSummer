#include "stdafx.h"
#include "GameManager.h"
#include "Scene/SceneManager.h"
#include "Scene/TitleScene.h"
#include "Component/Collision/CollisionManager.h"
#include "ProjectileManager.h"

GameManager::GameManager()
{
	CollisionManager::CreateInstance();
	ProjectileManager::CreateInstance();
	//PhysicsWorld::GetInstance()->SetGravity(Vector3(0.0f, -50000.0f, 0.0f));
	m_sceneManager = std::make_unique<SceneManager>();
	m_sceneManager->ChangeScene<TitleScene>();
}

GameManager::~GameManager()
{
}

void GameManager::Update()
{
	m_sceneManager->Update();
}

void GameManager::Draw()
{
	m_sceneManager->Draw();
}
