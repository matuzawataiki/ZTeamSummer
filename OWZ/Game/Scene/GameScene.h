#pragma once
#include "Scene/SceneBase.h"

class DestructibleTower;
class Soldier;
class GameScene : public SceneBase
{
public:
	GameScene();
	~GameScene();
private:
	Soldier* m_test = nullptr;
	DestructibleTower* m_tower = nullptr;

public:
	void Initialize() override;
	void Update(SceneManager& manager) override;
	void Draw() override;
	void Finalize() override;
};
