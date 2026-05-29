#pragma once
class ColliderComponent;
class Quadtree : public Noncopyable
{
public:
	Quadtree() = default;
	~Quadtree() = default;

	struct AABB {
		float minX, minZ, maxX, maxZ;

		float CenterX() const { return (minX + maxX) * 0.5f; }
		float CenterZ() const { return (minZ + maxZ) * 0.5f; }
		float HalfWidth() const { return (maxX - minX) * 0.5f; }
		float HalfHeight() const { return (maxZ - minZ) * 0.5f; }

		bool Intersects(const AABB& other) const {
			return !(other.minX > maxX || other.maxX < minX ||
				other.minZ > maxZ || other.maxZ < minZ);
		}

		bool Contains(const AABB& other) const {
			return other.minX >= minX && other.maxX <= maxX &&
				other.minZ >= minZ && other.maxZ <= maxZ;
		}
	};

	struct Config {
		float worldMinX = -10000.0f;		// ワールドの最小X
		float worldMinZ = -10000.0f;		// ワールドの最小Z
		float worldMaxX = 10000.0f;		// ワールドの最大X
		float worldMaxZ = 30000.0f;		// ワールドの最大Z
		int maxDepth = 6;				// 最大深度
		int maxObjectsPerNode = 10;		// ノードあたりの最大オブジェクト数
	};

private:
	/// <summary>
	/// Quadtreeのノード。
	/// </summary>
	struct Node {
		AABB bounds;
		int depth = 0;
		bool isSubdivided = false;
		std::vector<ColliderComponent*> objects;
		std::unique_ptr<Node> children[4];	// NW=0, NE=1, SW=2, SE=3
	};

	std::unique_ptr<Node> m_root;
	Config m_config;

public:
	/// <summary>
	/// Quadtreeを初期化する。
	/// </summary>
	void Init(const Config& config);

	/// <summary>
	/// 全ノードをクリアする。毎フレームの再構築前に呼ぶ。
	/// </summary>
	void Clear();

	/// <summary>
	/// コライダーをQuadtreeに挿入する。
	/// </summary>
	void Insert(ColliderComponent* collider);

	/// <summary>
	/// 衝突する可能性のあるペアを全て取得する。
	/// 同一ノードまたは親子関係にあるオブジェクト同士のペアのみ返す。
	/// </summary>
	void GetCollisionPairs(std::vector<std::pair<ColliderComponent*, ColliderComponent*>>& outPairs);

	/// <summary>
	/// 指定AABBと重なるコライダーを全て取得する。
	/// レイキャスト等で使用。
	/// </summary>
	void Query(const AABB& range, std::vector<ColliderComponent*>& outResults);

private:
	/// <summary>
	/// コライダーのXZ平面上のAABBを計算する。
	/// </summary>
	AABB CalcColliderAABB(ColliderComponent* collider);

	/// <summary>
	/// ノードを4分割する。
	/// </summary>
	void Subdivide(Node* node);

	/// <summary>
	/// ノードにオブジェクトを挿入する。
	/// </summary>
	void InsertToNode(Node* node, ColliderComponent* collider, const AABB& colliderAABB);

	/// <summary>
	/// ノード内のオブジェクト同士＋親から渡されたオブジェクトとのペアを収集する。
	/// </summary>
	void CollectPairs(
		Node* node,
		std::vector<ColliderComponent*>& inheritedObjects,
		std::vector<std::pair<ColliderComponent*, ColliderComponent*>>& outPairs
	);

	/// <summary>
	/// ノード内で範囲クエリを行う。
	/// </summary>
	void QueryNode(Node* node, const AABB& range, std::vector<ColliderComponent*>& outResults);
};

