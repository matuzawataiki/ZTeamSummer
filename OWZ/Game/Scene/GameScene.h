#pragma once
#include "Scene/SceneBase.h"
#include "InGameObject/Character/Enemy/Walk_Enemy.h"
#include "InGameObject/Character/Enemy/Middle_Boss.h"
#include <vector>
#include <memory>

class DestructibleObject;
class Soldier;
class MissionBase;
class GameScene : public SceneBase
{
public:
	GameScene();
	~GameScene();
private:
	Soldier* m_test = nullptr;
	DestructibleObject* m_tower = nullptr;
	DestructibleObject* m_tower2 = nullptr;

	MissionBase* m_currentMission = nullptr; // 現在進行中のミッション

	std::vector<std::shared_ptr<EnemyBase>> m_enemies; // 敵のリスト

public:
	void Initialize() override;
	void Update(SceneManager& manager) override;
	void Draw() override;
	void Finalize() override;


private:
	void LoadParameters();


};
