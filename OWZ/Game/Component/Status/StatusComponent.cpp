#include "stdafx.h"
#include "StatusComponent.h"

void StatusComponent::Init(Vector3 hp, float speed, float attacPower)
{
	m_hp.Init(hp.x, hp.y, hp.z);
	m_speed = speed;
	m_attacPower = attacPower;
}

void Buff::Update()
{
	if (m_isDead) { return; }
	if (!m_start || !m_update) { return; }

	if (!m_isStart) {
		m_start(m_target);
	}
	else {
		m_update(m_target);
	}

	m_buffTime -= g_gameTime->GetFrameDeltaTime();

	if (m_buffTime <= 0) {
		m_isDead = true;
	}	
}
