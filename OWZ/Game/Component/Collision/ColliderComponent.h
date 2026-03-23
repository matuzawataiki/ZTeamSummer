#pragma once
#include "CollisionDefine.h"

class ColliderComponent : public Component
{
	appClass(ColliderComponent);
public:
	ColliderComponent();
	~ColliderComponent();

	/// <summary>
	/// 衝突時に呼ばれるコールバック型。
	/// </summary>
	using HitCallback = std::function<void(const HitResult&)>;

private:
	PhysicsGhostObject m_ghostObject;
	EnCollisionCategory m_category = EnCollisionCategory::enCollisionCat_None;
	EnCollisionCategory m_categoryMask = EnCollisionCategory::enCollisionCat_All;
	HitCallback m_onHitCallback = nullptr;

	float m_radius;
	bool m_isCreated = false;

public:

	/// <summary>
	/// ボックス形状のコライダーを作成。
	/// </summary>
	/// <param name="size">ボックスの半径サイズ (各軸)</param>
	void CreateBox(const Vector3& size);

	/// <summary>
	/// 球形状のコライダーを作成。
	/// </summary>
	/// <param name="radius">球の半径</param>
	void CreateSphere(float radius);

	/// <summary>
	/// カプセル形状のコライダーを作成。
	/// </summary>
	/// <param name="radius">カプセルの半径</param>
	/// <param name="height">カプセルの高さ</param>
	void CreateCapsule(float radius, float height);

	// --- カテゴリ設定 ---

	/// <summary>
	/// 自分のコリジョンカテゴリを設定。
	/// </summary>
	void SetCategory(EnCollisionCategory category) { m_category = category; }

	/// <summary>
	/// 衝突対象のカテゴリマスクを設定。
	/// ビットANDで一致するカテゴリのみ衝突判定を行う。
	/// </summary>
	void SetCategoryMask(EnCollisionCategory mask) { m_categoryMask = mask; }

	/// <summary>
	/// 自分のカテゴリを取得。
	/// </summary>
	EnCollisionCategory GetCategory() const { return m_category; }

	/// <summary>
	/// 衝突対象マスクを取得。
	/// </summary>
	EnCollisionCategory GetCategoryMask() const { return m_categoryMask; }

	// --- コールバック ---

	/// <summary>
	/// 衝突時のコールバック関数を設定。
	/// </summary>
	void SetOnHitCallback(HitCallback callback) { m_onHitCallback = std::move(callback); }

	// --- 内部アクセス（CollisionManagerから使用）---

	/// <summary>
	/// PhysicsGhostObjectを取得。
	/// </summary>
	PhysicsGhostObject& GetGhostObject() { return m_ghostObject; }

	/// <summary>
	/// コリジョンのを取得。
	/// </summary>
	float GetRadius() { return m_radius; }

	/// <summary>
	/// コールバックを呼び出す。
	/// </summary>
	void NotifyHit(const HitResult& result) {
		if (m_onHitCallback) {
			m_onHitCallback(result);
		}
	}

	/// <summary>
	/// コライダーが作成済みかどうか。
	/// </summary>
	bool IsCreated() const { return m_isCreated; }

private:
	bool Start() override;
	void Update() override;

	/// <summary>
	/// TransformComponentの座標・回転をゴーストオブジェクトに同期する。
	/// </summary>
	void SyncTransform();
};

