#include "stdafx.h"
#include "Quadtree.h"
#include "Component/Collision/ColliderComponent.h"

void Quadtree::Init(const Config& config)
{
	m_config = config;
	m_root = std::make_unique<Node>();
	m_root->bounds = { config.worldMinX, config.worldMinZ, config.worldMaxX, config.worldMaxZ };
	m_root->depth = 0;
}

void Quadtree::Clear()
{
	if (m_root) {
		m_root->objects.clear();
		m_root->isSubdivided = false;
		for (int i = 0; i < 4; i++) {
			m_root->children[i].reset();
		}
	}
}

void Quadtree::Insert(ColliderComponent* collider)
{
	if (!collider->IsCreated() || !collider->IsActive()) {
		return;
	}
	AABB colliderAABB = CalcColliderAABB(collider);
	InsertToNode(m_root.get(), collider, colliderAABB);
}

Quadtree::AABB Quadtree::CalcColliderAABB(ColliderComponent* collider)
{
	AABB aabb = {};
	auto owner = collider->GetOwner();
	if (owner == nullptr) {
		return aabb;
	}
	auto transform = owner->GetComponent<TransformComponent>();
	if (transform == nullptr) {
		return aabb;
	}

	Vector3 pos = transform->GetPosition();

	float radius = collider->GetRadius();

	aabb.minX = pos.x - radius;
	aabb.maxX = pos.x + radius;
	aabb.minZ = pos.z - radius;
	aabb.maxZ = pos.z + radius;
	return aabb;
}

void Quadtree::InsertToNode(Node* node, ColliderComponent* collider, const AABB& colliderAABB)
{
	// 子ノードが存在する場合、完全に収まる子ノードに挿入を試みる
	if (node->isSubdivided) {
		for (int i = 0; i < 4; i++) {
			if (node->children[i]->bounds.Contains(colliderAABB)) {
				InsertToNode(node->children[i].get(), collider, colliderAABB);
				return;
			}
		}
		// どの子にも完全には入らない→このノードに格納
		node->objects.push_back(collider);
		return;
	}

	// このノードに追加
	node->objects.push_back(collider);

	// 最大数を超えたら分割（最大深度未満の場合のみ）
	if (static_cast<int>(node->objects.size()) > m_config.maxObjectsPerNode
		&& node->depth < m_config.maxDepth) {
		Subdivide(node);
	}

}

void Quadtree::Subdivide(Node* node)
{
	float cx = node->bounds.CenterX();
	float cz = node->bounds.CenterZ();
	int childDepth = node->depth + 1;

	// NW (0): 左上
	node->children[0] = std::make_unique<Node>();
	node->children[0]->bounds = { node->bounds.minX, cz, cx, node->bounds.maxZ };
	node->children[0]->depth = childDepth;

	// NE (1): 右上
	node->children[1] = std::make_unique<Node>();
	node->children[1]->bounds = { cx, cz, node->bounds.maxX, node->bounds.maxZ };
	node->children[1]->depth = childDepth;

	// SW (2): 左下
	node->children[2] = std::make_unique<Node>();
	node->children[2]->bounds = { node->bounds.minX, node->bounds.minZ, cx, cz };
	node->children[2]->depth = childDepth;

	// SE (3): 右下
	node->children[3] = std::make_unique<Node>();
	node->children[3]->bounds = { cx, node->bounds.minZ, node->bounds.maxX, cz };
	node->children[3]->depth = childDepth;

	node->isSubdivided = true;

	// 既存オブジェクトを子ノードに再分配
	std::vector<ColliderComponent*> remaining;
	for (auto* obj : node->objects) {
		AABB objAABB = CalcColliderAABB(obj);
		bool inserted = false;
		for (int i = 0; i < 4; i++) {
			if (node->children[i]->bounds.Contains(objAABB)) {
				node->children[i]->objects.push_back(obj);
				inserted = true;
				break;
			}
		}
		if (!inserted) {
			// 複数の子ノードにまたがるオブジェクトは親に残す
			remaining.push_back(obj);
		}
	}
	node->objects = remaining;
}

void Quadtree::GetCollisionPairs(std::vector<std::pair<ColliderComponent*, ColliderComponent*>>& outPairs)
{
	std::vector<ColliderComponent*> inherited;
	CollectPairs(m_root.get(), inherited, outPairs);
}

void Quadtree::CollectPairs(
	Node* node, 
	std::vector<ColliderComponent*>& inheritedObjects,
	std::vector<std::pair<ColliderComponent*, ColliderComponent*>>& outPairs)
{
	if (node == nullptr) {
		return;
	}

	// 1. このノード内のオブジェクト同士のペア
	for (size_t i = 0; i < node->objects.size(); i++) {
		for (size_t j = i + 1; j < node->objects.size(); j++) {
			outPairs.push_back({ node->objects[i], node->objects[j] });
		}
	}

	// 2. このノードのオブジェクトと、親から継承されたオブジェクトとのペア
	for (auto* inherited : inheritedObjects) {
		for (auto* obj : node->objects) {
			outPairs.push_back({ inherited, obj });
		}
	}

	// 3. 子ノードに対して再帰（このノード+親のオブジェクトを継承）
	if (node->isSubdivided) {
		// 親から引き継いだオブジェクト＋このノードのオブジェクトを子へ渡す
		std::vector<ColliderComponent*> nextInherited = inheritedObjects;
		nextInherited.insert(nextInherited.end(), node->objects.begin(), node->objects.end());

		for (int i = 0; i < 4; i++) {
			CollectPairs(node->children[i].get(), nextInherited, outPairs);
		}
	}
}

void Quadtree::Query(const AABB& range, std::vector<ColliderComponent*>& outResults)
{
	QueryNode(m_root.get(), range, outResults);
}

void Quadtree::QueryNode(Node* node, const AABB& range, std::vector<ColliderComponent*>& outResults)
{
	if (node == nullptr) {
		return;
	}

	// このノードの範囲とクエリ範囲が交差しなければスキップ
	if (!node->bounds.Intersects(range)) {
		return;
	}

	// このノードのオブジェクトを追加
	for (auto* obj : node->objects) {
		AABB objAABB = CalcColliderAABB(obj);
		if (range.Intersects(objAABB)) {
			outResults.push_back(obj);
		}
	}

	// 子ノードを再帰的に探索
	if (node->isSubdivided) {
		for (int i = 0; i < 4; i++) {
			QueryNode(node->children[i].get(), range, outResults);
		}
	}
}
