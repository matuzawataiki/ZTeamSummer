#include "stdafx.h"
#include "TitleScene.h"
#include "Scene/SceneManager.h"
#include "Scene/GameScene.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	m_titleImage = std::make_unique<SpriteRender>();
	m_titleImage->Init("Assets/image/title/testTitle.DDS", 1920, 1080);
}

void TitleScene::Update(SceneManager& manager)
{
	if (g_pad[0]->IsPress(enButtonF)) {
		manager.ChangeScene<GameScene>();
	}
}

void TitleScene::Draw()
{
	m_titleImage->Draw();
}

void TitleScene::Finalize()
{
}
