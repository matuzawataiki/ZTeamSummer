#include "stdafx.h"
#include "GameManager.h"
#include "Scene/SceneManager.h"
#include "Scene/TitleScene.h"

GameManager::GameManager()
{
	CollisionManager::CreateInstance();
	m_sceneManager = std::make_unique<SceneManager>();
	m_sceneManager->ChangeScene<TitleScene>();
}

GameManager::~GameManager()
{
	CollisionManager::DeleteInstance();
}

void GameManager::Update()
{
	m_sceneManager->Update();
	CollisionManager::GetInstance()->Update();
}

void GameManager::Draw()
{
	m_sceneManager->Draw();
}
