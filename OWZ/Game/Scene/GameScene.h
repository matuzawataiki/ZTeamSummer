#pragma once
#include "Scene/SceneBase.h"

class DestructibleObject;
class Soldier;
class MissionManager;
class GameScene : public SceneBase
{
public:
	GameScene();
	~GameScene();
private:
	Soldier* m_test = nullptr;
	DestructibleObject* m_tower = nullptr;
	DestructibleObject* m_tower2 = nullptr;

	std::unique_ptr<MissionManager> m_missionManager;

public:
	void Initialize() override;
	void Update(SceneManager& manager) override;
	void Draw() override;
	void Finalize() override;
};
