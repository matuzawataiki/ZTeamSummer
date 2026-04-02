#pragma once
#include "InGameObject/Character/Enemy/EnemyBase.h"


class Walk_Enemy : public EnemyBase
{
public:
	Walk_Enemy() = default;
	~Walk_Enemy() = default;


	bool Start() override;
	void Update() override;
	void Draw(RenderContext& rc) override;


protected:
	void OnUpdate() override;


};

