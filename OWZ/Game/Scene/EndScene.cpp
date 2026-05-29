#include "stdafx.h"
#include "EndScene.h"
#include "TargetManager.h"
#include "Scene/SceneManager.h"
#include "Scene/TitleScene.h"

EndScene::EndScene()
{
	m_titleImage = std::make_unique<SpriteRender>();
	m_titleImage->Init("Assets/image/title/testEndTitle.DDS", 1920, 1080);
	m_titleFont = std::make_unique<FontRender>();
	int poitn = TargetManager::GetInstance()->GetPoint();
	wchar_t buffer[32];
	swprintf(buffer, 32, L"%d", poitn);

	m_titleFont->SetText(buffer);
	m_titleFont->SetPosition(Vector3::Zero);
	m_titleFont->SetColor(Vector4::Black);
}

EndScene::~EndScene()
{
	TargetManager::DeleteInstance();
}

void EndScene::Update(SceneManager & manager)
{
	if (g_pad[0]->IsTrigger(enButtonA)) {
		manager.ChangeScene<TitleScene>();
	}
}

void EndScene::Draw()
{
	RenderContext rc;
	m_titleFont->Draw(rc);
	m_titleImage->Draw();
}

void EndScene::Finalize()
{

}
