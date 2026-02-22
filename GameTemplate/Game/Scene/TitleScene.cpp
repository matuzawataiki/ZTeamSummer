#include "stdafx.h"
#include "TitleScene.h"
#include "Scene/SceneManager.h"
#include "Scene/GameScene.h"

void TitleScene::Initialize()
{
	m_titleImage = std::make_unique<SpriteRender>();
	m_titleImage->Init("Assets/image/title/testTitle.DDS", 1920, 1080);
}

void TitleScene::Update(SceneManager& manager)
{
	if (g_pad[0]->IsPress(enButtonF)) {
		manager.ChangeScene(std::make_unique<GameScene>());
	}
}

void TitleScene::Draw(RenderContext& rc)
{
	m_titleImage->Draw(rc);
}

void TitleScene::Finalize()
{
}
