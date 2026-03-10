#include "stdafx.h"
#include "Transform.h"

Transform::Transform()
{
}

Transform::~Transform()
{
}

void Transform::SetParent(std::shared_ptr<Transform> parent, std::shared_ptr<Transform> children)
{
	if (m_parent) {
		m_parent->m_children.erase(
			std::remove(
				m_parent->m_children.begin(),
				m_parent->m_children.end(),
				children
			),
			m_parent->m_children.end()
		);
	}

	m_parent = parent;

	if (m_parent) {
		m_parent->m_children.push_back(children);
	}

	SetDirty();
}
