#include "k2EngineLowPreCompile.h"
#include "Component.h"

void nsK2EngineLow::Component::UpdateWrapper()
{
	if (Start()) {
		m_isStart = true;
	}
	if (m_isActive && m_isStart) {
		Update();
	}
}
