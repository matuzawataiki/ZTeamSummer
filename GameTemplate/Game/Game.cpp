#include "stdafx.h"
#include "Game.h"
#include "Scene/TitleScene.h"


bool Game::Start()
{
	// g_renderingEngine->DisableRaytracing();

	m_sceneManager = std::make_unique<SceneManager>();
	m_sceneManager->ChangeScene(std::make_unique<TitleScene>());

	return true;
}

void Game::Update()
{
	m_sceneManager->Update();
}

void Game::Render(RenderContext& rc)
{
	m_sceneManager->Draw(rc);
}