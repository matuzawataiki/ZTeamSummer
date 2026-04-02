#pragma once
#include "InGameObject/Character/CharacterBase.h"


class EnemyBase : public CharacterBase
{
public:
	EnemyBase() = default;
	~EnemyBase() = default;


	bool Start() override;
	void Update() override;
	void Draw(RenderContext& rc) override;


	/** GameSceneで1回だけ呼ぶ */
	void SetPlayerTransform(std::shared_ptr<TransformComponent> t)
	{
		if (m_ai) m_ai->SetPlayerTransform(t);
	}


protected:
	virtual void OnUpdate() override {}


};

