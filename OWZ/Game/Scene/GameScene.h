#pragma once
#include "Scene/SceneBase.h"

class Soldier;
class StageObject;
class GameScene : public SceneBase
{
public:
	GameScene();
	~GameScene();
private:
	Soldier* testPlayer = nullptr;
	StageObject* testStage = nullptr;

public:
	void Initialize() override;
	void Update(SceneManager& manager) override;
	void Draw() override;
	void Finalize() override;
};
