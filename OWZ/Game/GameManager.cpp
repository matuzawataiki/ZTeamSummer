#include "stdafx.h"
#include "GameManager.h"
#include "Scene/SceneManager.h"
#include "Scene/TitleScene.h"

GameManager::GameManager()
{
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
