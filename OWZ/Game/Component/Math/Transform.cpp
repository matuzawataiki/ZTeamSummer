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
	if (std::shared_ptr<Transform> currentParent = m_parent.lock()) {
		currentParent->m_children.erase(
			std::remove(
				currentParent->m_children.begin(),
				currentParent->m_children.end(),
				children
			),
			currentParent->m_children.end()
		);
	}

	m_parent = parent;

	if (parent) {
		parent->m_children.push_back(children);
	}

	SetDirty();
}
