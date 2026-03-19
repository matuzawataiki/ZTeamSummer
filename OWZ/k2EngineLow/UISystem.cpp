#include "k2EngineLowPreCompile.h"
#include "UISystem.h"

nsK2EngineLow::UISystem::UISystem()
{
	const int count = static_cast<int>(CanvasType::Count);
	for (int i = 0; i < count; ++i) {
		m_canvases[i] = std::make_unique<Canvas>();
	}
}

void nsK2EngineLow::UISystem::Update()
{
	for (size_t i = 0; i < ToIndex(CanvasType::Count); ++i)
	{
		m_canvases[i].Update();
	}
}

void nsK2EngineLow::UISystem::Render(RenderContext& rc)
{
	for (size_t i = 0; i < ToIndex(CanvasType::Count); ++i)
	{
		m_canvases[i].Render(rc);
	}
}
