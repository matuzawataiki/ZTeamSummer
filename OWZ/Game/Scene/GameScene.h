#pragma once
#include "Scene/SceneBase.h"
class GoalObject;
class Soldier;
class GameScene : public SceneBase
{
public:
	GameScene();
	~GameScene();
private:
	std::unique_ptr<Soldier> m_player;
	std::unique_ptr<GoalObject> m_goal;

public:
	void Initialize() override;
	void Update(SceneManager& manager) override;
	void Draw() override{}
	void Finalize() override;
};
