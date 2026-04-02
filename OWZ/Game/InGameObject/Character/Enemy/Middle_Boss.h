#pragma once
#include "InGameObject/Character/Enemy/EnemyBase.h"


class Middle_Boss : public EnemyBase
{
public:
	Middle_Boss() = default;
	~Middle_Boss() = default;


	bool Start() override;
	void Update() override;
	void Draw(RenderContext& rc) override;


protected:
	void OnUpdate() override;


};

