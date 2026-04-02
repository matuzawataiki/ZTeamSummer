#include "stdafx.h"
#include "CharacterBase.h"


bool CharacterBase::Start()
{
	return true;
}


void CharacterBase::Update()
{
	if (m_health && m_health->IsDead()) return;
	if (m_health) m_health->UpdateWrapper();
	if (m_move) m_move->UpdateWrapper();
	if (m_attack) m_attack->UpdateWrapper();
	if (m_ai) m_ai->UpdateWrapper();
}


void CharacterBase::Draw(RenderContext& rc)
{
	// 描画処理はここで行う
}


void CharacterBase::InitComponents(ParameterManager* params, int index, bool withAI)
{
	auto* hp = params->GetParameter<HealthParameter>(index);
	auto* move = params->GetParameter<MoveParameter>(index);
	auto* atk = params->GetParameter<AttackParameter>(index);

   if (hp) m_health = std::make_unique<HealthComponent>(*hp);
	if (move) m_move = std::make_unique<MoveComponent>(*move);
	if (atk) m_attack = std::make_unique<AttackComponent>(atk);

	if (withAI)
	{
		auto* ai = params->GetParameter<AIBehaviorParameter>(index);
		if (ai) m_ai = std::make_unique<AIBehaviorComponent>(ai);
	}
}