#pragma once
#include "Component/Math/TransformComponent.h"
#include "Component/Parameter/HealthComponent.h"
#include "Component/Parameter/MoveComponent.h"
#include "Component/Parameter/AttackComponent.h"
#include "Component/Parameter/AIBehaviorComponent.h"
#include "Parameter/ParameterManager.h"
#include "gameObject/GameObject.h"
#include <memory>


enum class CharacterIndex : int
{
	Player = 0,
	Walk_Enemy = 1,
	Fly_Enemy = 2,
	Middle_Boss = 3,
	Boss = 4,
};


class CharacterBase : public GameObject
{
public:
	/** コンストラクタ */
	CharacterBase() = default;


	/** デストラクタ */
	virtual ~CharacterBase() = default;


	/** 初期化処理 */
	virtual bool Start();


	/** 更新処理 */
	virtual void Update();


	/** 描画処理 */
	virtual void Draw(RenderContext& rc);


	/** ダメージを受ける処理 */
	void TakeDamage(float amount)
	{
		if (m_health)
		{
			m_health->TakeDamage(amount);
		}
	}


	/** 死亡しているか確認しているフラグの取得 */
	bool IsDead() const
	{
		return m_health ? m_health->IsDead() : false;
	}
	

	std::shared_ptr<TransformComponent> GetTransform() const { return m_transform; }
	HealthComponent* GetHealthComponent() const { return m_health.get(); }
	MoveComponent* GetMoveComponent() const { return m_move.get(); }
	AttackComponent* GetAttackComponent() const { return m_attack.get(); }
	AIBehaviorComponent* GetAIBehaviorComponent() const { return m_ai.get(); }


protected:
	virtual void OnUpdate() {}


	/** コンポーネントの初期化 */
	void InitComponents(ParameterManager* params, int index, bool withAI);


	std::shared_ptr<TransformComponent> m_transform;
	std::unique_ptr<HealthComponent> m_health;
	std::unique_ptr<MoveComponent> m_move;
	std::unique_ptr<AttackComponent> m_attack;
	std::unique_ptr<AIBehaviorComponent> m_ai;

};