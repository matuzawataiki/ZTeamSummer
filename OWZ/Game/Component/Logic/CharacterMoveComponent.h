#pragma once

class StatusComponent;
class CharactorColliderComponent;
class CharacterMoveComponent : public Component
{
	appClass(CharacterMoveComponent)
private:
	StatusComponent* m_status = nullptr;
	CharactorColliderComponent* m_charactorCollider = nullptr;
	
	Vector3 m_moveSpeed = Vector3::Zero;
	float m_jumpVelocity = -500.0f;
	float m_deltaTime = 0.0f;
	float m_beginFlag = 0.0f;
	bool m_isJump = false;

private:
	bool Start() override;
	void Update() override;

};

