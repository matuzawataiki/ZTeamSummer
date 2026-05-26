#include "k2EngineLowPreCompile.h"
#include "Component.h"
#include "GameObject.h"
namespace nsK2EngineLow
{
	void Component::UpdateWrapper()
	{
		if (m_isActive && m_isStart) {
			Update();
		}
		else if (m_isActive && !m_isStart) {
			if (Start()) {
				m_isStart = true;
			}
		}
	}
}
