#include "stdafx.h"
#include "Sprint.h"
#include "Component/Status/StatusComponent.h"

void Sprint::Fire()
{
	auto statusComponent = m_parent->GetComponent<StatusComponent>();
	statusComponent->SetSpeedBonus(75);

	m_isUse = true;
}

void Sprint::Reset()
{
	auto statusComponent = m_parent->GetComponent<StatusComponent>();
	statusComponent->SetSpeedBonus(0);

	m_isUse = false;
}
