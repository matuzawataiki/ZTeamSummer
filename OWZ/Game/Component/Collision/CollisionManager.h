#pragma once
#include "CollisionDefine.h"
#include "Quadtree.h"

class ColliderComponent;
class CollisionManager : public Noncopyable
{
	static CollisionManager* m_instance;
private:
	CollisionManager();
	~CollisionManager() = default;

private:
	std::vector<std::weak_ptr<ColliderComponent>> m_colliders;
	Quadtree m_quadtree;

public:
	static void CreateInstance() {
		if (!m_instance) {
			m_instance = new CollisionManager;
		}
	}
	static void DeleteInstance() {
		delete m_instance;
		m_instance = nullptr;
	}
	static CollisionManager* GetInstance() {
		return m_instance;
	}

	/// <summary>
	/// コライダーを登録する。ColliderComponentの形状作成時に自動で呼ばれる。
	/// </summary>
	void Register(std::shared_ptr<ColliderComponent> collider);

	/// <summary>
	/// コライダーの登録を解除する。ColliderComponentの破棄時に自動で呼ばれる。
	/// </summary>
	void Unregister(std::shared_ptr<ColliderComponent> collider);

	/// <summary>
	/// 全コライダー間の衝突判定を実行する。
	/// </summary>
	void Update();

	/// <summary>
	/// レイキャストを行い、最初にヒットしたオブジェクトの情報を返す。
	/// 射撃判定やライン・オブ・サイトの確認に使う。
	/// </summary>
	/// <param name="origin">レイの始点</param>
	/// <param name="direction">レイの方向（正規化済み）</param>
	/// <param name="maxDistance">最大距離</param>
	/// <param name="outResult">ヒット結果の出力先</param>
	/// <param name="mask">衝突対象カテゴリマスク</param>
	/// <returns>ヒットした場合true</returns>
	bool Raycast(
		const Vector3& origin,
		const Vector3& direction,
		float maxDistance,
		HitResult& outResult,
		uint32_t mask = enCollisionCat_All
	);

	/// <summary>
	/// 半径付きレイキャスト（SphereCast）を行う。
	/// 球体をレイに沿ってスイープし、最初にヒットしたオブジェクトを返す。
	/// 射撃判定で弾道に太さを持たせたい場合に使う。
	/// </summary>
	/// <param name="origin">レイの始点</param>
	/// <param name="direction">レイの方向（正規化済み）</param>
	/// <param name="maxDistance">最大距離</param>
	/// <param name="radius">球の半径（レイの太さ）</param>
	/// <param name="outResult">ヒット結果の出力先</param>
	/// <param name="mask">衝突対象カテゴリマスク</param>
	/// <returns>ヒットした場合true</returns>
	bool SphereCast(
		const Vector3& origin,
		const Vector3& direction,
		float maxDistance,
		float radius,
		HitResult& outResult,
		uint32_t mask = enCollisionCat_All
	);

	/// <summary>
	/// Quadtreeの設定を変更する（ワールドサイズ等）。
	/// 呼ばなければデフォルト値が使われる。
	/// </summary>
	void SetQuadtreeConfig(const Quadtree::Config& config);

private:
	/// <summary>
	/// 2つのコライダー間の衝突判定を行う。
	/// </summary>
	void CheckCollision(ColliderComponent* a, ColliderComponent* b);
};

