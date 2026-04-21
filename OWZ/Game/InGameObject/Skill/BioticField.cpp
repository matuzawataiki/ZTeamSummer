#include "stdafx.h"
#include "BioticField.h"
#include "InGameObject/Skill/HealingArea.h"
#include "Component/Graphics/ModelComponent.h"

BioticField::BioticField() = default;

BioticField::~BioticField() = default;

void BioticField::Init()
{
	AddComponent<TransformComponent>();
	AddComponent<ModelComponent>();
	
	m_maxCooldown = 25;
	m_maxDuration = 8;

	m_healingArea = std::make_unique<HealingArea>();
	m_healingArea->Init(12, 40);
	m_healingArea->Deactivate();

}

void BioticField::Fire()
{
	m_isUse = true;

	m_healingArea->Activate();
	m_duration = m_maxDuration;

}

void BioticField::Update()
{
	if (m_cooldownTimer > 0 || m_canCooldown) {
		m_cooldownTimer -= g_gameTime->GetFrameDeltaTime();
	}

	if (m_isUse) {
		m_duration -= g_gameTime->GetFrameDeltaTime();
		if (m_duration < 0) {
			m_isUse = false;
			m_healingArea->Deactivate();
		}
	}
}
