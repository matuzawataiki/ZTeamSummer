#pragma once
#include "Scene/SceneBase.h"

class DestructibleCore;
class CoreTower;
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

private:
	std::vector<std::unique_ptr<DestructibleCore>> m_cores;    // 破壊可能なコアのリスト
	std::vector<std::unique_ptr<CoreTower>> m_towers;          // コアを守るタワーのリスト
};
