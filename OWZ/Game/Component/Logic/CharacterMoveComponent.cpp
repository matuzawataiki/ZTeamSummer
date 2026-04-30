#include "stdafx.h"
#include "CharacterMoveComponent.h"
#include "Component/Status/StatusComponent.h"
#include "Component/Collision/CharactorColliderComponent.h"

bool CharacterMoveComponent::Start()
{
	m_status = GetComponent<StatusComponent>();
	m_charactorCollider = GetComponent<CharactorColliderComponent>();
	return true;
}

void CharacterMoveComponent::Update()
{
	float x = 0;
	float z = 0;

	x = g_pad[0]->GetLStickXF();
	z = g_pad[0]->GetLStickYF();

	Vector3 moveVolume = { x, 0, z };
	moveVolume.Normalize();
	moveVolume = moveVolume * m_status->GetSpeed() * 100.0f;
	moveVolume += moveVolume * m_status->GetSpeedBonus();

	moveVolume.y = -500.0f;
	m_charactorCollider->SetMoveSpeed(moveVolume);
}
