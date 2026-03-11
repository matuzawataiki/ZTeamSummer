#pragma once
#include "Scene/SceneBase.h"
class TitleScene : public SceneBase
{
public:
	TitleScene();
	~TitleScene();
private:
	std::unique_ptr<SpriteRender> m_titleImage;

public:
	void Initialize() override;
	void Update(SceneManager& manager) override;
	void Draw() override;
	void Finalize() override;
};

