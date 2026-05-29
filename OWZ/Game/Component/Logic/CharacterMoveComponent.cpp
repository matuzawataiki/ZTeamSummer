#include "stdafx.h"
#include "CharacterMoveComponent.h"
#include "Component/Status/StatusComponent.h"
#include "Component/Collision/CharactorColliderComponent.h"

bool CharacterMoveComponent::Start()
{
	m_status = m_owner->GetComponent<StatusComponent>();
	m_charactorCollider = m_owner->GetComponent<CharactorColliderComponent>();
	return true;
}

void CharacterMoveComponent::Update()
{
	float x = 0;
	float z = 0;

	x = g_pad[0]->GetLStickXF();
	z = g_pad[0]->GetLStickYF();

	Vector3 moveVolume = Vector3( x, 0.0f, z );
	moveVolume.Normalize();
	moveVolume = moveVolume * m_status->GetSpeed() * 100.0f;
	moveVolume += moveVolume * m_status->GetSpeedBonus();

	Vector3 forward = g_camera3D->GetForward();
	forward.y = 0.0f;
	forward.Normalize();

	Vector3 right = g_camera3D->GetRight();
	right.y = 0.0f;
	right.Normalize();

	Vector3 direction = g_camera3D->GetForward();
	direction.y = 0;
	direction.Normalize();
	Vector3 moveSpeed;

	moveSpeed = (forward * moveVolume.z) + (right * moveVolume.x);

	if(m_charactorCollider->IsOnGround() && !m_isJump) {
		if (g_pad[0]->IsTrigger(enButtonA)) {
			m_isJump = true;
			m_jumpVelocity = 1000.0f;
			m_deltaTime = 0.0f;
		}

		m_moveSpeed = moveSpeed;
	}
	else {
		float gravity = -500.0f;
		if (m_isJump && m_jumpVelocity > -500.0f) {
			m_deltaTime += g_gameTime->GetFrameDeltaTime() * 0.3;
			m_jumpVelocity -= 500.0f * m_deltaTime;
			gravity = m_jumpVelocity;
		}

		moveSpeed = m_moveSpeed + moveSpeed * 0.5;

		float masatu = g_gameTime->GetFrameDeltaTime() * 100;

		if (m_moveSpeed.x > 0.0f) {
			m_moveSpeed.x -= masatu;
			m_moveSpeed.x = max(0.0f, m_moveSpeed.x);
		}
		else if (m_moveSpeed.x < 0.0f) {
			m_moveSpeed.x += masatu;
			m_moveSpeed.x = min(0.0f, m_moveSpeed.x);
		}

		if (m_moveSpeed.z > 0.0f) {
			m_moveSpeed.z -= masatu;
			m_moveSpeed.z = max(0.0f, m_moveSpeed.z);
		}				
		else if (m_moveSpeed.z < 0.0f) {
			m_moveSpeed.z += masatu;
			m_moveSpeed.z = min(0.0f, m_moveSpeed.z);
		}

		moveSpeed.y = gravity;

		if (m_beginFlag > 0.5f) {
			if (m_charactorCollider->IsOnGround()) {
				m_isJump = false;
				m_beginFlag = false;
			}
		}
		else {
			m_beginFlag += g_gameTime->GetFrameDeltaTime();
		}
	}

	m_charactorCollider->SetMoveSpeed(moveSpeed);
}
