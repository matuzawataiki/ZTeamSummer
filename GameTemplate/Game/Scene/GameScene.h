#pragma once
#include "Scene/SceneBase.h"

class GameScene : public SceneBase
{
public:
	void Initialize() override;
	void Update(SceneManager& manager) override;
	void Draw(RenderContext& rc) override;
	void Finalize() override;
};
