#include "stdafx.h"
#include "UISystem.h"

UISystem* UISystem::m_instance = nullptr;

UISystem::UISystem()
{
	const int count = ToIndex(CanvasType::Count);
	for (int i = 0; i < count; ++i) {
		m_canvases[i] = std::make_unique<Canvas>();
	}
}

void UISystem::CreateInstance()
{
	if (m_instance == nullptr) {
		m_instance = new UISystem();
	}
}

void UISystem::DestroyInstance()
{
	delete m_instance;
	m_instance = nullptr;
}

UISystem& UISystem::Get()
{
	K2_ASSERT(m_instance != nullptr, "UISystem has not been created.");
	return *m_instance;
}
void UISystem::Update()
{
	for (size_t i = 0; i < ToIndex(CanvasType::Count); ++i)
	{
		m_canvases[i]->Update();
	}
}

void UISystem::Render()
{
	for (size_t i = 0; i < ToIndex(CanvasType::Count); ++i)
	{
		m_canvases[i]->Render();
	}
}