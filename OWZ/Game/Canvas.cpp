#include "stdafx.h"
#include "Canvas.h"
#include "UIObfect.h"

void Canvas::AddUI(const std::shared_ptr<UIObject>& ui)
{
	if (ui == nullptr) {
		return;
	}

	// 二重追加防止
	auto existsInMain = std::find(m_uiObjects.begin(), m_uiObjects.end(), ui);
	if (existsInMain != m_uiObjects.end()) {
		return;
	}

	auto existsInPending = std::find(m_pendingAddObjects.begin(), m_pendingAddObjects.end(), ui);
	if (existsInPending != m_pendingAddObjects.end()) {
		return;
	}

	if (m_isUpdating) {
		m_pendingAddObjects.push_back(ui);
	}
	else {
		m_uiObjects.push_back(ui);
	}
}

void Canvas::RemoveUI(const std::shared_ptr<UIObject>& ui)
{
	if (ui == nullptr) {
		return;
	}

	if (m_isUpdating) {
		auto existsInPending = std::find(m_pendingRemoveObjects.begin(), m_pendingRemoveObjects.end(), ui);
		if (existsInPending == m_pendingRemoveObjects.end()) {
			m_pendingRemoveObjects.push_back(ui);
		}
	}
	else {
		auto it = std::remove(m_uiObjects.begin(), m_uiObjects.end(), ui);
		m_uiObjects.erase(it, m_uiObjects.end());
	}
}

void Canvas::Clear()
{
	if (m_isUpdating) {
		m_pendingRemoveObjects = m_uiObjects;
	}
	else {
		m_uiObjects.clear();
		m_pendingAddObjects.clear();
		m_pendingRemoveObjects.clear();
	}
}

void Canvas::FlushPending()
{
	// 削除を先に反映
	for (const auto& ui : m_pendingRemoveObjects) {
		auto it = std::remove(m_uiObjects.begin(), m_uiObjects.end(), ui);
		m_uiObjects.erase(it, m_uiObjects.end());
	}
	m_pendingRemoveObjects.clear();

	// 追加を反映
	for (const auto& ui : m_pendingAddObjects) {
		if (ui == nullptr) {
			continue;
		}

		auto it = std::find(m_uiObjects.begin(), m_uiObjects.end(), ui);
		if (it == m_uiObjects.end()) {
			m_uiObjects.push_back(ui);
		}
	}
	m_pendingAddObjects.clear();

	//　UIオブジェクトの中で破棄リクエストが来ているものを削除
	auto it = std::remove_if(
		m_uiObjects.begin(),
		m_uiObjects.end(),
		[](const std::shared_ptr<UIObject>& ui)
		{
			return ui == nullptr || ui->IsDestroyRequested();
		}
	);
	m_uiObjects.erase(it, m_uiObjects.end());
}

bool Canvas::Start()
{
	for (auto& ui : m_uiObjects) {
		if (ui == nullptr) {
			continue;
		}

		ui->StartWrapper();
	}

	return true;
}

void Canvas::Update()
{
	m_isUpdating = true;

	for (auto& ui : m_uiObjects) {
		if (ui == nullptr) {
			continue;
		}

		ui->StartWrapper();
		ui->UpdateWrapper();
	}

	m_isUpdating = false;

	FlushPending();
}

void Canvas::Render()
{
	for (auto& ui : m_uiObjects) {
		if (ui == nullptr) {
			continue;
		}

		ui->Render();
	}
}