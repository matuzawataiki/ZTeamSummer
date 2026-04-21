#include "k2EngineLowPreCompile.h"
#include "GameObject.h"

nsK2EngineLow::GameObject::GameObject() = default;
nsK2EngineLow::GameObject::~GameObject() = default;

void nsK2EngineLow::GameObject::UpdateWrapper()
{
	if (m_isActive && m_isStart) {
		Update();
		Render();
		for (auto& component : m_componentList) {
			component.second->UpdateWrapper();
		}

		for (auto& children : m_children) {
			children.second->StartWrapper();
			children.second->UpdateWrapper();
		}
	}
}

