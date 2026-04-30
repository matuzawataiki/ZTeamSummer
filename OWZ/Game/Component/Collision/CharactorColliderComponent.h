#pragma once
class CharactorColliderComponent : public Component
{
	appClass(CharactorColliderComponent);

private:
	bool		m_isInited = false;				//!<初期化済み？
	bool 		m_isJump = false;				//!<ジャンプ中？
	bool		m_isOnGround = true;			//!<地面の上にいる？
	float		m_radius = 0.0f;				//!<カプセルコライダーの半径。
	float		m_height = 0.0f;				//!<カプセルコライダーの高さ。

	Vector3		m_moveSpeed = Vector3::Zero;

	Vector3		m_force = Vector3::Zero;

public:
	void Init();

	void Update() override;

	void SetMoveSpeed(Vector3& moveSpeed) {	m_moveSpeed = moveSpeed;}
};

