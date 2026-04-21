#include "stdafx.h"
#include "CharacterMoveComponent.h"
#include "Component/Status/StatusComponent.h"
#include "Component/Collision/RigidBodyComponent.h"

bool CharacterMoveComponent::Start()
{
	m_status = GetComponent<StatusComponent>();
	m_rigidBody = GetComponent<RigidBodyComponent>();

	return true;
}

void CharacterMoveComponent::Update()
{
	float x = 0;
	float z = 0;

	if (g_pad[0]->IsPress(enButtonW)) z += 1;
	if (g_pad[0]->IsPress(enButtonS)) z -= 1;
	if (g_pad[0]->IsPress(enButtonD)) x += 1;
	if (g_pad[0]->IsPress(enButtonA)) x -= 1;

	Vector3 moveVolume = { x, 0, z };
	moveVolume.Normalize();

	m_rigidBody->AddForce(moveVolume * m_status->GetSpeed() + moveVolume * m_status->GetSpeedBonus());
}
