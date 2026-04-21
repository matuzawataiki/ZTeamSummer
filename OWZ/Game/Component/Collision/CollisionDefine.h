#pragma once

/// <summary>
/// コリジョンのカテゴリ（ビットフラグ）。
/// 衝突させたい組み合わせをマスクで制御する。
/// </summary>
static enum EnCollisionCategory : uint32_t {
	enCollisionCat_None         = 0,
	enCollisionCat_Player       = 1 << 0,
	enCollisionCat_Enemy        = 1 << 1,
	enCollisionCat_PlayerBullet = 1 << 2,
	enCollisionCat_EnemyBullet  = 1 << 3,
	enCollisionCat_Environment  = 1 << 4,
	enCollisionCat_Trigger      = 1 << 5,
	enCollisionCat_Heel			= 1 << 6,
	// ユーザー拡張用
	enCollisionCat_User1        = 1 << 16,
	enCollisionCat_User2        = 1 << 17,
	enCollisionCat_All          = 0xFFFFFFFF,
};

/// <summary>
/// 衝突結果を格納する構造体。
/// コールバックやレイキャストの結果として使用する。
/// </summary>
struct HitResult {
	GameObject* hitObject = nullptr;	// 衝突相手のGameObject
	Vector3 hitPos    = Vector3::Zero;					// 衝突点
	Vector3 hitNormal = Vector3::Zero;					// 衝突面の法線
	EnCollisionCategory hitCategory = enCollisionCat_None;	// 相手のカテゴリ
};
