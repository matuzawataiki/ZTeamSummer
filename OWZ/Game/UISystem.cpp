#include "stdafx.h"
#include "UISystem.h"

UISystem::UISystem()
{
	const int count = ToIndex(CanvasType::Count);
	for (int i = 0; i < count; ++i) {
		m_canvases[i] = std::make_unique<Canvas>();
	}
}

void UISystem::Update()
{
	for (size_t i = 0; i < ToIndex(CanvasType::Count); ++i)
	{
		m_canvases[i]->Update();
	}
}

void UISystem::Render(RenderContext& rc)
{
	for (size_t i = 0; i < ToIndex(CanvasType::Count); ++i)
	{
		//m_canvases[i].Render(rc);
	}
}