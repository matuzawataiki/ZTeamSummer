#pragma once
#include "Scene/SceneBase.h"
class TitleScene : public SceneBase
{
private:
	std::unique_ptr<SpriteRender> m_titleImage;

public:
	void Initialize() override;
	void Update(SceneManager& manager) override;
	void Draw(RenderContext& rc) override;
	void Finalize() override;
};

