#include "k2EngineLowPreCompile.h"
#include "Transform.h"
namespace nsK2EngineLow
{
	Transform::Transform() {}

	Transform::~Transform() {}

	void Transform::SetParent(Transform* parent, Transform* children)
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

		if (parent) {
			parent->m_children.push_back(children);
		}

		SetDirty();
	}
}
