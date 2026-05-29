#pragma once
#include "Scene/SceneBase.h"

class EndScene : public SceneBase
{
public:
	EndScene();
	~EndScene();

private:
	std::unique_ptr<SpriteRender> m_titleImage;
	std::unique_ptr<FontRender> m_titleFont;

public:
	void Initialize() override {}
	void Update(SceneManager& manager) override;
	void Draw() override;
	void Finalize() override;
};

