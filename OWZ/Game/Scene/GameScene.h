#pragma once
#include "Scene/SceneBase.h"

class DestructibleObject;
class Soldier;
class MissionBase;
class Enemy;
class GameScene : public SceneBase
{
public:
	GameScene();
	~GameScene();
private:
	Soldier* m_test = nullptr;
	Enemy* m_enemy = nullptr;
	DestructibleObject* m_tower = nullptr;
	DestructibleObject* m_tower2 = nullptr;

	MissionBase* m_currentMission = nullptr; // 現在進行中のミッション

public:
	void Initialize() override;
	void Update(SceneManager& manager) override;
	void Draw() override;
	void Finalize() override;
};
