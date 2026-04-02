#pragma once
#include "gameObject/Component.h"
#include "Parameter/General/AttackParameter.h"


class AttackComponent : public Component
{
	appClass(AttackComponent)


public:
	explicit AttackComponent(const AttackParameter* param) : m_param(param) {}


	/**	攻撃を試みる。攻撃が成功した場合はダメージを返す。 */
	float TryAttack();


	/**	攻撃範囲内にいるか */
	bool IsInRange(float dist) const { return dist <= m_param->m_range; }


	/**	攻撃範囲を取得 */
	float GetRange() const { return m_param->m_range; }


private:
	/** 初期化処理 */
	bool Start() override { return true; }


	/** 更新処理 */
	void Update() override;


private:
	const AttackParameter* m_param;
	float m_cooldown = 0.0f;


};

