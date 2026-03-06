#include "stdafx.h"
#include "TransformComponent.h"

TransformComponent::TransformComponent()
{
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::SetParent(TransformComponent* parent)
{
	if (m_parent) {
		m_parent->m_childern.erase(
			std::remove(
				m_parent->m_childern.begin(),
				m_parent->m_childern.end(),
				this
			),
			m_parent->m_childern.end()
		);
	}

	m_parent = std::make_shared<TransformComponent>(parent);

	if (m_parent) {
		m_parent->m_childern.push_back(std::make_shared<TransformComponent>(this));
	}

	SetDirty();
}
