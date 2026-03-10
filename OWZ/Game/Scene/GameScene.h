#pragma once
#include "Scene/SceneBase.h"

class Soldier;
class GameScene : public SceneBase
{
public:
	GameScene();
	~GameScene();
private:
	Soldier* m_test = nullptr;

public:
	void Initialize() override;
	void Update(SceneManager& manager) override;
	void Draw() override;
	void Finalize() override;
};
