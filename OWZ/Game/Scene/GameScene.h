#pragma once
#include "Scene/SceneBase.h"

class Soldier;
class GameScene : public SceneBase
{
public:
	GameScene();
	~GameScene();
private:
	std::shared_ptr<Soldier> m_test;

public:
	void Initialize() override;
	void Update(SceneManager& manager) override;
	void Draw() override;
	void Finalize() override;
};
