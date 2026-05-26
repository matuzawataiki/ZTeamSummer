#include "stdafx.h"
#include "CollisionManager.h"
#include "Component/Collision/ColliderComponent.h"

CollisionManager* CollisionManager::m_instance = nullptr;

CollisionManager::CollisionManager() {
	Quadtree::Config config;
	m_quadtree.Init(config);
}

void CollisionManager::Register(ColliderComponent* collider)
{
	for (auto it = m_colliders.begin(); it != m_colliders.end(); ) {
		if (*it) {
			if (*it == collider) {
				return;
			}
			++it;
		}
		else {
			it = m_colliders.erase(it);
		}
	}

	m_colliders.push_back(collider);
}

void CollisionManager::Unregister(ColliderComponent* collider)
{
	m_colliders.erase(
		std::remove_if(
			m_colliders.begin(),
			m_colliders.end(),
			[collider](const ColliderComponent* w) {
				return !w || w == collider;
			}
		),
		m_colliders.end()
	);
}

void CollisionManager::Update()
{
	// 1. Quadtreeをクリアして再構築
	m_quadtree.Clear();
	for (auto collider : m_colliders) {
		m_quadtree.Insert(collider);
	}

	// 2. Quadtreeから衝突候補ペアを取得
	std::vector<std::pair<ColliderComponent*, ColliderComponent*>> pairs;
	m_quadtree.GetCollisionPairs(pairs);

	// 3. 候補ペアに対してのみ詳細な衝突判定を実行
	//将来的にはマルチスレッドで
	for (auto& pair : pairs) {
		CheckCollision(pair.first, pair.second);
	}
}

void CollisionManager::CheckCollision(ColliderComponent* a, ColliderComponent* b)
{
	if (!a->IsCreated() || !b->IsCreated()) {
		return;
	}
	if (!a->IsActive() || !b->IsActive()) {
		return;
	}

	// カテゴリマスクによるフィルタリング
	// aのマスクにbのカテゴリが含まれているか
	bool aWantsB = (a->GetCategoryMask() & b->GetCategory()) != 0;
	// bのマスクにaのカテゴリが含まれているか
	bool bWantsA = (b->GetCategoryMask() & a->GetCategory()) != 0;

	if (!aWantsB && !bWantsA) {
		// どちらも相手のカテゴリに反応しない
		return;
	}

	// PhysicsWorldのContactTestで物理的な重なりを判定
	bool isHit = false;
	PhysicsWorld::GetInstance()->ContactTest(
		&b->GetGhostObject().GetbtCollisionObject(),
		[&](const btCollisionObject& contactObject) {
			if (a->GetGhostObject().IsSelf(contactObject)) {
				isHit = true;
			}
		}
	);

	if (!isHit) {
		return;
	}

	// HitResultを構築してコールバックを呼ぶ

	// aに通知（bが当たった）
	if (aWantsB) {
		HitResult resultForA;
		resultForA.hitObject = b->GetOwner();
		resultForA.hitCategory = b->GetCategory();
		// hitPos/hitNormal は ContactTest では詳細が取れないためゼロ
		a->NotifyHit(resultForA);
	}

	// bに通知（aが当たった）
	if (bWantsA) {
		HitResult resultForB;
		resultForB.hitObject = a->GetOwner();
		resultForB.hitCategory = a->GetCategory();
		b->NotifyHit(resultForB);
	}
}

bool CollisionManager::Raycast(
	const Vector3& origin,
	const Vector3& direction, 
	float maxDistance, 
	HitResult& outResult, 
	uint32_t mask)
{
	// レイの終点を計算
	Vector3 rayEnd = origin;
	Vector3 dir = direction;
	dir.Scale(maxDistance);
	rayEnd.Add(dir);

	// PhysicsWorldのRayTestを使用
	Vector3 hitPos;
	bool isHit = PhysicsWorld::GetInstance()->RayTest(origin, rayEnd, hitPos);

	if (!isHit) {
		return false;
	}

	outResult.hitPos = hitPos;

	// ヒットしたオブジェクトを特定する
	// 登録済みColliderの中からヒット位置に最も近いものを探す
	float closestDist = FLT_MAX;
	ColliderComponent* closestCollider = nullptr;

	for (auto& collider : m_colliders) {
		if (!collider) {
			continue;
		}

		if (!collider->IsCreated() || !collider->IsActive()) {
			continue;
		}
		// マスクチェック
		if ((mask & collider->GetCategory()) == 0) {
			continue;
		}

		// コライダーに対してContactTestではなく、個別にレイテストで確認
		// ここでは簡易的に、レイ上で最初にヒットしたものを返す
		auto owner = collider->GetOwner();
		if (owner == nullptr) {
			continue;
		}
		auto transform = owner->GetComponent<TransformComponent>();
		if (transform == nullptr) {
			continue;
		}

		// ヒット位置とコライダーの距離で最近接を判定
		Vector3 colPos = transform->GetPosition();
		Vector3 diff;
		diff.Subtract(hitPos, colPos);
		float dist = diff.Length();
		if (dist < closestDist) {
			closestDist = dist;
			closestCollider = collider;
		}
	}

	if (closestCollider != nullptr) {
		outResult.hitObject = closestCollider->GetOwner();
		outResult.hitCategory = closestCollider->GetCategory();
	}

	return true;
}

bool CollisionManager::SphereCast(
	const Vector3& origin, 
	const Vector3& direction, 
	float maxDistance,
	float radius, 
	HitResult& outResult, 
	uint32_t mask)
{
	// レイの終点を計算
	Vector3 rayEnd = origin;
	Vector3 dir = direction;
	dir.Scale(maxDistance);
	rayEnd.Add(dir);

	// btSphereShapeを作成（スイープする球）
	btSphereShape sphereShape(radius);

	// 始点と終点のトランスフォームを設定
	btTransform fromTransform;
	fromTransform.setIdentity();
	fromTransform.setOrigin(btVector3(origin.x, origin.y, origin.z));

	btTransform toTransform;
	toTransform.setIdentity();
	toTransform.setOrigin(btVector3(rayEnd.x, rayEnd.y, rayEnd.z));

	// カスタムConvexResultCallback：最も近いヒットを記録
	struct SphereCastCallback : public btCollisionWorld::ClosestConvexResultCallback {
		Vector3 m_hitPos;
		const btCollisionObject* m_hitCollisionObject = nullptr;

		SphereCastCallback(const btVector3& from, const btVector3& to)
			: ClosestConvexResultCallback(from, to)
		{
		}

		btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace) override
		{
			// 最も近い結果のみを保持
			btScalar result = ClosestConvexResultCallback::addSingleResult(convexResult, normalInWorldSpace);
			if (hasHit()) {
				m_hitPos.x = m_hitPointWorld.x();
				m_hitPos.y = m_hitPointWorld.y();
				m_hitPos.z = m_hitPointWorld.z();
				m_hitCollisionObject = convexResult.m_hitCollisionObject;
			}
			return result;
		}
	};

	SphereCastCallback callback(
		btVector3(origin.x, origin.y, origin.z),
		btVector3(rayEnd.x, rayEnd.y, rayEnd.z)
	);

	// ConvexSweepTestを実行
	PhysicsWorld::GetInstance()->ConvexSweepTest(
		&sphereShape,
		fromTransform,
		toTransform,
		callback
	);

	if (!callback.hasHit()) {
		return false;
	}

	outResult.hitPos = callback.m_hitPos;

	// ヒットしたbtCollisionObjectから、登録済みColliderを特定する
	for (auto& collider : m_colliders) {
		if (!collider) {
			continue;
		}
		if (!collider->IsCreated() || !collider->IsActive()) {
			continue;
		}
		// マスクチェック
		if ((mask & collider->GetCategory()) == 0) {
			continue;
		}
		// btCollisionObjectの一致で特定
		if (collider->GetGhostObject().IsSelf(*callback.m_hitCollisionObject)) {
			outResult.hitObject = collider->GetOwner();
			outResult.hitCategory = collider->GetCategory();
			return true;
		}
	}

	// 物理ワールドの何かに当たったが、登録済みColliderではなかった
	outResult.hitObject = nullptr;
	outResult.hitCategory = enCollisionCat_None;
	return true;
}

void CollisionManager::SetQuadtreeConfig(const Quadtree::Config& config)
{
	m_quadtree.Init(config);
}