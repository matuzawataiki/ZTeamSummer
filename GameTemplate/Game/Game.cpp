#include "stdafx.h"
#include "Game.h"


bool Game::Start()
{
	m_modelRender.Init("Assets/bush1.tkm");

	return true;
}

void Game::Update()
{
	// g_renderingEngine->DisableRaytracing();

	if (g_pad[0]->IsPress(enButtonA)) {
		m_pos.z += 10.0f;
	}
	if (g_pad[0]->IsPress(enButtonB)) {
		m_pos.z -= 10.0f;
	}
	if (g_pad[0]->IsPress(enButtonLeft)) {
		m_rot.AddRotationDegY(10.0f);
	}

	m_modelRender.SetPosition(m_pos);
	m_modelRender.SetRotation(m_rot);

	m_modelRender.Update();
}

void Game::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}