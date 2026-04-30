#pragma once
#include "CollisionDefine.h"

/// <summary>
/// 剛体（RigidBody）コンポーネント。
/// 物理シミュレーションによる移動・衝突応答を行う。
/// ColliderComponentがトリガー（衝突検知のみ）であるのに対し、
/// こちらは物理的な力・速度・重力の影響を受ける。
/// </summary>
class RigidBodyComponent : public Component
{
	appClass(RigidBodyComponent);
public:
	RigidBodyComponent();
	~RigidBodyComponent();

	// --- 形状作成 ---

	/// <summary>
	/// 剛体を作成。
	/// </summary>
	/// <param name="size">ボックスの半径サイズ (各軸)</param>
	/// <param name="mass">質量（0で静的オブジェクト）</param>
	/// <param name="restitution">反発係数（0〜1）</param>
	void CreateRigidBody(float mass = 0.0f, float restitution = 0.0f);

	// --- 速度・力 ---

	/// <summary>
	/// 力を加える。
	/// </summary>
	/// <param name="force">加える力</param>
	/// <param name="relPos">力を加える相対座標</param>
	void AddForce(const Vector3& force, const Vector3& relPos = Vector3::Zero);

	/// <summary>
	/// 線形速度を設定。
	/// </summary>
	void SetLinearVelocity(const Vector3& velocity);

	/// <summary>
	/// 線形速度を取得。
	/// </summary>
	Vector3 GetLinearVelocity() const;

	/// <summary>
	/// 角速度を設定。
	/// </summary>
	void SetAngularVelocity(const Vector3& velocity);

	// --- 移動・回転の制限 ---

	/// <summary>
	/// 移動可能な軸を設定（0で固定、1で自由）。
	/// </summary>
	void SetLinearFactor(float x, float y, float z);

	/// <summary>
	/// 回転可能な軸を設定（0で固定、1で自由）。
	/// </summary>
	void SetAngularFactor(float x, float y, float z);

	// --- 摩擦 ---

	/// <summary>
	/// 摩擦力を設定。
	/// </summary>
	void SetFriction(float friction);

	// --- 座標同期 ---

	/// <summary>
	/// 物理ワールドの座標・回転をTransformComponentに反映する。
	/// Update内で自動呼出し。
	/// </summary>
	void SyncToTransform();

	/// <summary>
	/// TransformComponentの座標・回転を物理ワールドに反映する。
	/// テレポートなど、物理を無視して位置を変えたい場合に使う。
	/// </summary>
	void SyncFromTransform();

	/// <summary>
	/// 剛体が作成済みかどうか。
	/// </summary>
	bool IsCreated() const { return m_isCreated; }

	/// <summary>
	/// 内部のRigidBodyへの参照を取得。
	/// </summary>
	RigidBody& GetRigidBody() { return m_rigidBody; }

	void AddGroundType() {
		m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_Ground);
	}

private:
	bool Start() override;
	void Update() override;

private:
	RigidBody m_rigidBody;

	bool m_isCreated = false;
};
